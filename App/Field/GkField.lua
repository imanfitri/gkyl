-- GkField ---------------------------------------------------------------------
--
-- App support code: Gyrokinetic fields phi and apar, solved by
-- (perpendicular) Poisson and Ampere equations.
-- 
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

local AdiosCartFieldIo = require "Io.AdiosCartFieldIo"
local Constants        = require "Lib.Constants"
local DataStruct       = require "DataStruct"
local LinearTrigger    = require "LinearTrigger"
local Mpi              = require "Comm.Mpi"
local Proto            = require "Lib.Proto"
local Updater          = require "Updater"
local xsys             = require "xsys"
local FieldBase        = require "App.Field.FieldBase"
local Species          = require "App.Species"
local Time             = require "Lib.Time"
local math             = require("sci.math").generic
local diff             = require("sci.diff")

local GkField = Proto(FieldBase.FieldBase)

-- This ctor simply stores what is passed to it and defers actual
-- construction to the fullInit() method below.
function GkField:init(tbl)
   GkField.super.init(self, tbl)
   self.tbl = tbl
end

-- Actual function for initialization. This indirection is needed as
-- we need the app top-level table for proper initialization.
function GkField:fullInit(appTbl)
   local tbl = self.tbl -- Previously store table.
   
   self.ioMethod = "MPI"
   self.evolve = xsys.pickBool(tbl.evolve, true) -- By default evolve field.

   self.isElectromagnetic = xsys.pickBool(tbl.isElectromagnetic, false) -- Electrostatic by default.

   -- Create triggers to write fields.
   if tbl.nFrame then
      self.ioTrigger = LinearTrigger(0, appTbl.tEnd, tbl.nFrame)
   else
      self.ioTrigger = LinearTrigger(0, appTbl.tEnd, appTbl.nFrame)
   end

   self.ioFrame = 0 -- Frame number for IO.

   self.writeGhost = xsys.pickBool(appTbl.writeGhost, false)

   -- Get boundary condition settings.
   -- These will be checked for consistency when the solver is initialized.
   if tbl.phiBcLeft then self.phiBcLeft          = tbl.phiBcLeft end
   if tbl.phiBcRight then self.phiBcRight        = tbl.phiBcRight end
   if tbl.phiBcBottom then self.phiBcBottom      = tbl.phiBcBottom end
   if tbl.phiBcTop then self.phiBcTop            = tbl.phiBcTop end
   if tbl.phiBcBack then self.phiBcBack          = tbl.phiBcBack end
   if tbl.phiBcFront then self.phiBcFront        = tbl.phiBcFront end
   if tbl.aparBcLeft then self.aparBcLeft        = tbl.aparBcLeft end
   if tbl.aparBcRight then self.aparBcRight      = tbl.aparBcRight end
   if tbl.aparBcBottom then self.aparBcBottom    = tbl.aparBcBottom end
   if tbl.aparBcTop then self.aparBcTop          = tbl.aparBcTop end
   if appTbl.periodicDirs then self.periodicDirs = appTbl.periodicDirs end

   -- For storing integrated energies.
   self.phi2     = DataStruct.DynVector { numComponents = 1 }
   self.apar2    = DataStruct.DynVector { numComponents = 1 }
   self.esEnergy = DataStruct.DynVector { numComponents = 1 }
   self.emEnergy = DataStruct.DynVector { numComponents = 1 }

   self.adiabatic = false
   self.discontinuousPhi  = xsys.pickBool(tbl.discontinuousPhi, false)
   self.discontinuousApar = xsys.pickBool(tbl.discontinuousApar, true)

   -- For ndim=1 only.
   self.kperp2 = tbl.kperp2

   -- Allow user to specify polarization weight. will be calculated automatically if not specified.
   self.polarizationWeight = tbl.polarizationWeight

   -- Determine whether to use linearized polarization term in poisson equation, which uses background density in polarization weight
   -- if not, uses full time-dependent density in polarization weight.
   self.linearizedPolarization = xsys.pickBool(tbl.linearizedPolarization, true)
   self.uniformPolarization    = xsys.pickBool(tbl.uniformPolarization, true)

   if self.isElectromagnetic then
      self.mu0 = tbl.mu0 or Constants.MU0
   end

   self.externalPhi = tbl.externalPhi
   if self.externalPhi and self.evolve then 
      print("GkField: warning... specifying externalPhi will make initial phi inconsistent with f") 
   end
   assert(not tbl.initPhiFunc, "GkField: initPhiFunc deprecated. Use externalPhi.")

   -- This allows us to apply a multiplicative time dependence to externalPhi.
   if tbl.externalPhiTimeDependence then
      self.externalPhiTimeDependence = tbl.externalPhiTimeDependence
   else
      self.externalPhiTimeDependence = false
   end

   self.bcTime = 0.0 -- Timer for BCs.

   self._first     = true
   self._firstStep = true
end

-- Methods for EM field object.
function GkField:hasEB() return true, self.isElectromagnetic end
function GkField:setCfl() end
function GkField:setIoMethod(ioMethod) self.ioMethod = ioMethod end
function GkField:setBasis(basis) self.basis = basis end
function GkField:setGrid(grid) self.grid = grid; self.ndim = self.grid:ndim() end

function GkField:alloc(nRkDup)
   -- Allocate fields needed in RK update.
   -- nField is related to number of RK stages.
   self.potentials = {}
   self.nRkDup = nRkDup
   for i = 1, nRkDup do
      self.potentials[i] = {}
      self.potentials[i].phi = DataStruct.Field {
         onGrid        = self.grid,
         numComponents = self.basis:numBasis(),
         ghost         = {1, 1}
      }
      self.potentials[i].phi:clear(0.0)
      if self.isElectromagnetic then
         self.potentials[i].apar = DataStruct.Field {
            onGrid        = self.grid,
            numComponents = self.basis:numBasis(),
            ghost         = {1, 1}
         }
         self.potentials[i].dApardt = DataStruct.Field {
            onGrid        = self.grid,
            numComponents = self.basis:numBasis(),
            ghost         = {1, 1}
         }
         self.potentials[i].apar:clear(0.0)
         self.potentials[i].dApardt:clear(0.0)
      end
   end

   self.dApardtProv = DataStruct.Field {
      onGrid        = self.grid,
      numComponents = self.basis:numBasis(),
      ghost         = {1, 1}
   }

   -- Create fields for total charge and current densities.
   self.chargeDens = DataStruct.Field {
      onGrid        = self.grid,
      numComponents = self.basis:numBasis(),
      ghost         = {1, 1}
   }
   self.currentDens = DataStruct.Field {
      onGrid        = self.grid,
      numComponents = self.basis:numBasis(),
      ghost         = {1, 1}
   }
   -- Set up constant dummy field.
   self.unitWeight = DataStruct.Field {
      onGrid        = self.grid,
      numComponents = self.basis:numBasis(),
      ghost         = {1, 1},
   }
   local initUnit = Updater.ProjectOnBasis {
      onGrid   = self.grid,
      basis    = self.basis,
      evaluate = function (t,xn)
                    return 1.0
                 end,
      projectOnGhosts = true,
   }
   initUnit:advance(0.,{},{self.unitWeight})

   -- Set up some other fields.
   self.weight = DataStruct.Field {
      onGrid        = self.grid,
      numComponents = self.basis:numBasis(),
      ghost         = {1, 1},
   }
   self.laplacianWeight = DataStruct.Field {
      onGrid        = self.grid,
      numComponents = self.basis:numBasis(),
      ghost         = {1, 1},
   }
   self.modifierWeight = DataStruct.Field {
      onGrid        = self.grid,
      numComponents = self.basis:numBasis(),
      ghost         = {1, 1},
   }
end

-- Solve for initial fields self-consistently 
-- from initial distribution function.
function GkField:initField(species)
   if self.externalPhi then
      local evalOnNodes = Updater.EvalOnNodes {
         onGrid          = self.grid,
         basis           = self.basis,
         evaluate        = self.externalPhi,
         projectOnGhosts = true
      }
      self.externalPhiFld = DataStruct.Field {
         onGrid        = self.grid,
         numComponents = self.basis:numBasis(),
         ghost         = {1, 1}
      }
      evalOnNodes:advance(0.0, {}, {self.externalPhiFld})
      for i = 1, self.nRkDup do
         if self.externalPhiTimeDependence then
            self.potentials[i].phi:combine(self.externalPhiTimeDependence(0.0),self.externalPhiFld)
         else
            self.potentials[i].phi:copy(self.externalPhiFld)
         end
      end
   else
      -- Solve for initial phi.
      self:advance(0.0, species, 1, 1)
   end

   local polyOrder = self.basis:polyOrder()

   if self.isElectromagnetic then
      -- Solve for initial Apar.
      local apar = self.potentials[1].apar
      self.currentDens:clear(0.0)
      for nm, s in pairs(species) do
         self.currentDens:accumulate(s:getCharge(), s:getMomDensity())
      end
      self.aparSlvr:advance(0.0, {self.currentDens}, {apar})

      -- Decrease effective polynomial order in z of apar by setting the highest order z coefficients to 0.
      if self.ndim == 1 or self.ndim == 3 then -- Only have z direction in 1d or 3d (2d is assumed to be x,y).
         local localRange = apar:localRange()
         local indexer    = apar:genIndexer()
         local ptr        = apar:get(1)

         -- Loop over all cells.
         for idx in localRange:rowMajorIter() do
            self.grid:setIndex(idx)
            
            apar:fill(indexer(idx), ptr)
            if self.ndim == 1 then
               ptr:data()[polyOrder] = 0.0
            else -- ndim == 3.
               if polyOrder == 1 then
                  ptr:data()[3] = 0.0
                  ptr:data()[5] = 0.0
                  ptr:data()[6] = 0.0
                  ptr:data()[7] = 0.0
               elseif polyOrder == 2 then
                  ptr:data()[9]  = 0.0
                  ptr:data()[13] = 0.0
                  ptr:data()[14] = 0.0
                  ptr:data()[15] = 0.0
                  ptr:data()[16] = 0.0
                  ptr:data()[17] = 0.0
                  ptr:data()[18] = 0.0
                  ptr:data()[19] = 0.0
               end
            end
         end
      end

      -- Clear dApar/dt ... will be solved for before being used.
      self.potentials[1].dApardt:clear(0.0)
   end

   -- Apply BCs and update ghosts.
   self:applyBc(0, self.potentials[1])
end

function GkField:rkStepperFields()
   return self.potentials
end

-- For RK timestepping for non-elliptic fields (e.g. only apar).
function GkField:copyRk(outIdx, aIdx)
   if self.isElectromagnetic and self:rkStepperFields()[aIdx] then 
      self:rkStepperFields()[outIdx].apar:copy(self:rkStepperFields()[aIdx].apar)
   end
end
-- For RK timestepping for non-elliptic fields (e.g. only apar).
function GkField:combineRk(outIdx, a, aIdx, ...)
   if self.isElectromagnetic and self:rkStepperFields()[aIdx] then
      local args = {...} -- Package up rest of args as table.
      local nFlds = #args/2
      self:rkStepperFields()[outIdx].apar:combine(a, self:rkStepperFields()[aIdx].apar)
      for i = 1, nFlds do -- Accumulate rest of the fields.
         self:rkStepperFields()[outIdx].apar:accumulate(args[2*i-1], self:rkStepperFields()[args[2*i]].apar)
      end	 
   end
end

function GkField:suggestDt()
   return GKYL_MAX_DOUBLE
end
function GkField:clearCFL()
end

function GkField:createSolver(species, funcField)
   -- Get adiabatic species info.
   for nm, s in pairs(species) do
      if Species.AdiabaticSpecies.is(s) then
         self.adiabatic = true
         self.adiabSpec = s
      end
   end
   assert((self.adiabatic and self.isElectromagnetic) == false, "GkField: cannot use adiabatic response for electromagnetic case")

   -- Set up FEM solver for Poisson equation to solve for phi.
   local gxx, gxy, gyy
   if funcField.geo then 
     gxx = funcField.geo.gxx
     gxy = funcField.geo.gxy
     gyy = funcField.geo.gyy
   end
   self.phiSlvr = Updater.FemPoisson {
     onGrid   = self.grid,
     basis    = self.basis,
     bcLeft   = self.phiBcLeft,
     bcRight  = self.phiBcRight,
     bcBottom = self.phiBcBottom,
     bcTop    = self.phiBcTop,
     periodicDirs = self.periodicDirs,
     zContinuous  = not self.discontinuousPhi,
     gxx = gxx,
     gxy = gxy,
     gyy = gyy,
   }
   -- when using a linearizedPolarization term in Poisson equation,
   -- the weights on the terms are constant scalars
   if self.linearizedPolarization then
      -- if not provided, calculate species-dependent weight on polarization term == sum_s m_s n_s / B^2
      if not self.polarizationWeight then 
         self.polarizationWeight = 0.0
         for nm, s in pairs(species) do
            if Species.GkSpecies.is(s) then
               self.polarizationWeight = self.polarizationWeight + s:getPolarizationWeight()
            end
         end
      end
      -- if not adiabatic, and polarization weight still not set, assume it is 1
      if self.polarizationWeight == 0.0 and not self.adiabatic then self.polarizationWeight = 1.0 end

      -- set up scalar multipliers on laplacian and modifier terms in Poisson equation
      local laplacianConstant, modifierConstant
 
      if self.ndim==1 then
         assert(self.kperp2, "GkField: must specify kperp2 for ndim=1")
         laplacianConstant = 0.0 
         modifierConstant = self.kperp2*self.polarizationWeight 
      else 
         laplacianConstant = -self.polarizationWeight 
         modifierConstant = 0.0 
      end

      if self.adiabatic then 
         modifierConstant = modifierConstant + self.adiabSpec:getQneutFac() 
      end

      self.laplacianWeight:combine(laplacianConstant, self.unitWeight)
      self.modifierWeight:combine(modifierConstant, self.unitWeight)

      if laplacianConstant ~= 0 then self.phiSlvr:setLaplacianWeight(self.laplacianWeight) end
      if modifierConstant ~= 0 then self.phiSlvr:setModifierWeight(self.modifierWeight) end
   end
   -- when not using linearizedPolarization, weights are set each step in advance method

   if self.isElectromagnetic then 
     local ndim = self.ndim
     local laplacianConstant, modifierConstant
     -- NOTE: aparSlvr only used to solve for initial Apar
     -- at all other times Apar is timestepped using dApar/dt
     self.aparSlvr = Updater.FemPoisson {
       onGrid   = self.grid,
       basis    = self.basis,
       bcLeft   = self.aparBcLeft,
       bcRight  = self.aparBcRight,
       bcBottom = self.aparBcBottom,
       bcTop    = self.aparBcTop,
       periodicDirs = self.periodicDirs,
       zContinuous  = not self.discontinuousApar,
       gxx = gxx,
       gxy = gxy,
       gyy = gyy,
     }
     if ndim==1 then
        laplacianConstant = 0.0
        modifierConstant = self.kperp2/self.mu0
     else
        laplacianConstant = -1.0/self.mu0
        modifierConstant = 0.0
     end
     self.laplacianWeight:combine(laplacianConstant, self.unitWeight)
     self.modifierWeight:combine(modifierConstant, self.unitWeight)
     if laplacianConstant ~= 0 then self.aparSlvr:setLaplacianWeight(self.laplacianWeight) end
     if modifierConstant ~= 0 then self.aparSlvr:setModifierWeight(self.modifierWeight) end

     self.dApardtSlvr = Updater.FemPoisson {
       onGrid   = self.grid,
       basis    = self.basis,
       bcLeft   = self.aparBcLeft,
       bcRight  = self.aparBcRight,
       bcBottom = self.aparBcBottom,
       bcTop    = self.aparBcTop,
       periodicDirs = self.periodicDirs,
       zContinuous  = not self.discontinuousApar,
       gxx = gxx,
       gxy = gxy,
       gyy = gyy,
     }
     if ndim==1 then
        laplacianConstant = 0.0
        modifierConstant  = 1.0
     else
        laplacianConstant = -1.0/self.mu0
        modifierConstant  = 1.0
     end
     self.laplacianWeight:combine(laplacianConstant, self.unitWeight)
     self.modifierWeight:combine(modifierConstant, self.unitWeight)
     if laplacianConstant ~= 0 then self.dApardtSlvr:setLaplacianWeight(self.laplacianWeight) end
     if modifierConstant ~= 0 then self.dApardtSlvr:setModifierWeight(self.modifierWeight) end

     -- separate solver for additional step for p=1
     if self.basis:polyOrder() == 1 then
        self.dApardtSlvr2 = Updater.FemPoisson {
          onGrid   = self.grid,
          basis    = self.basis,
          bcLeft   = self.aparBcLeft,
          bcRight  = self.aparBcRight,
          bcBottom = self.aparBcBottom,
          bcTop    = self.aparBcTop,
          periodicDirs = self.periodicDirs,
          zContinuous  = not self.discontinuousApar,
          gxx = gxx,
          gxy = gxy,
          gyy = gyy,
        }
        if ndim==1 then
           laplacianConstant = 0.0
           modifierConstant  = 1.0
        else
           laplacianConstant = -1.0/self.mu0
           modifierConstant  = 1.0
        end
        self.laplacianWeight:combine(laplacianConstant, self.unitWeight)
        self.modifierWeight:combine(modifierConstant, self.unitWeight)
        if laplacianConstant ~= 0 then self.dApardtSlvr2:setLaplacianWeight(self.laplacianWeight) end
        if modifierConstant ~= 0 then self.dApardtSlvr2:setModifierWeight(self.modifierWeight) end
     end
   end

   -- Need to set this flag so that field calculated self-consistently at end of full RK timestep.
   self.isElliptic = true

   if self.isElectromagnetic and self.basis:polyOrder() == 1 then 
      self.nstep = 3 
   elseif self.isElectromagnetic then
      self.nstep = 2
   end
end

function GkField:createDiagnostics()
   -- Create Adios object for field I/O.
   self.fieldIo = AdiosCartFieldIo {
      elemType   = self.potentials[1].phi:elemType(),
      method     = self.ioMethod,
      writeGhost = self.writeGhost,
      metaData   = {
	 polyOrder = self.basis:polyOrder(),
	 basisType = self.basis:id()
      },
   }

   -- Updaters for computing integrated quantities.
   self.int2Calc = Updater.CartFieldIntegratedQuantCalc {
      onGrid   = self.grid,
      basis    = self.basis,
      quantity = "V2"
   }
   if self.ndim == 1 then
      self.energyCalc = Updater.CartFieldIntegratedQuantCalc {
         onGrid   = self.grid,
         basis    = self.basis,
         quantity = "V2"
      }
   elseif self.basis:polyOrder()==1 then -- GradPerpV2 only implemented for p=1 currently.
      self.energyCalc = Updater.CartFieldIntegratedQuantCalc {
         onGrid   = self.grid,
         basis    = self.basis,
         quantity = "GradPerpV2"
      }
   end
end

function GkField:write(tm, force)
   if self.evolve then
      -- Compute integrated quantities over domain.
      self.int2Calc:advance(tm, { self.potentials[1].phi }, { self.phi2 })
      if self.isElectromagnetic then 
        self.int2Calc:advance(tm, { self.potentials[1].apar }, { self.apar2 })
      end
      if self.linearizedPolarization then
         local esEnergyFac = .5*self.polarizationWeight
         if self.ndim == 1 then esEnergyFac = esEnergyFac*self.kperp2 end
         if self.energyCalc then self.energyCalc:advance(tm, { self.potentials[1].phi, esEnergyFac }, { self.esEnergy }) end
      else
         -- Something.
      end
      if self.isElectromagnetic then 
        local emEnergyFac = .5/self.mu0
        if self.ndim == 1 then emEnergyFac = emEnergyFac*self.kperp2 end
        if self.energyCalc then self.energyCalc:advance(tm, { self.potentials[1].apar, emEnergyFac}, { self.emEnergy }) end
      end
      
      if self.ioTrigger(tm) or force then
	 self.fieldIo:write(self.potentials[1].phi, string.format("phi_%d.bp", self.ioFrame), tm, self.ioFrame)
         if self.isElectromagnetic then 
	   self.fieldIo:write(self.potentials[1].apar, string.format("apar_%d.bp", self.ioFrame), tm, self.ioFrame)
	   self.fieldIo:write(self.potentials[1].dApardt, string.format("dApardt_%d.bp", self.ioFrame), tm, self.ioFrame)
         end
	 self.phi2:write(string.format("phi2_%d.bp", self.ioFrame), tm, self.ioFrame)
	 self.esEnergy:write(string.format("esEnergy_%d.bp", self.ioFrame), tm, self.ioFrame)
	 if self.isElectromagnetic then
	    self.apar2:write(string.format("apar2_%d.bp", self.ioFrame), tm, self.ioFrame)
	    self.emEnergy:write(string.format("emEnergy_%d.bp", self.ioFrame), tm, self.ioFrame)
	 end
	 
	 self.ioFrame = self.ioFrame+1
      end
   else
      -- If not evolving species, don't write anything except initial conditions.
      if self.ioFrame == 0 then
	 self.fieldIo:write(self.potentials[1].phi, string.format("phi_%d.bp", self.ioFrame), tm, self.ioFrame)
         if self.isElectromagnetic then 
	   self.fieldIo:write(self.potentials[1].apar, string.format("apar_%d.bp", self.ioFrame), tm, self.ioFrame)
	   self.fieldIo:write(self.potentials[1].dApardt, string.format("dApardt_%d.bp", self.ioFrame), tm, self.ioFrame)
         end
      end
      self.ioFrame = self.ioFrame+1
   end
end

function GkField:writeRestart(tm)
   -- (the final "false" prevents writing of ghost cells).
   self.fieldIo:write(self.potentials[1].phi, "phi_restart.bp", tm, self.ioFrame, false)
   self.fieldIo:write(self.phiSlvr:getLaplacianWeight(), "laplacianWeight_restart.bp", tm, self.ioFrame, false)
   self.fieldIo:write(self.phiSlvr:getModifierWeight(), "modifierWeight_restart.bp", tm, self.ioFrame, false)
   if self.isElectromagnetic then
     self.fieldIo:write(self.potentials[1].apar, "apar_restart.bp", tm, self.ioFrame, false)
   end

   -- (the final "false" prevents flushing of data after write).
   self.phi2:write("phi2_restart.bp", tm, self.ioFrame, false)

end

function GkField:readRestart()
   -- This read of restart file of phi is only to get frame
   -- numbering correct. The forward Euler recomputes the potential
   -- before updating the hyperbolic part.
   local tm, fr = self.fieldIo:read(self.potentials[1].phi, "phi_restart.bp")
   self.phi2:read("phi2_restart.bp", tm)

   self.fieldIo:read(self.laplacianWeight, "laplacianWeight_restart.bp")
   self.fieldIo:read(self.modifierWeight, "modifierWeight_restart.bp")
   self.phiSlvr:setLaplacianWeight(self.laplacianWeight)
   if self.adiabatic or self.ndim == 1 then self.phiSlvr:setModifierWeight(self.modifierWeight) end

   if self.isElectromagnetic then
      self.fieldIo:read(self.potentials[1].apar, "apar_restart.bp")
   end

   self:applyBc(0, self.potentials[1])

   self.ioFrame = fr 
   -- Iterate triggers.
   self.ioTrigger(tm)
end

-- Not needed for GK.
function GkField:accumulateCurrent(dt, current, em)
end

-- Solve for electrostatic potential phi.
function GkField:advance(tCurr, species, inIdx, outIdx)
   local potCurr = self:rkStepperFields()[inIdx]
   local potRhs  = self:rkStepperFields()[outIdx]
   
   if self.evolve or (self._first and not self.externalPhi) then
      if self.externalPhiTimeDependence then
         potCurr.phi:combine(self.externalPhiTimeDependence(tCurr), self.externalPhiFld)
      else
         self.chargeDens:clear(0.0)
         for nm, s in pairs(species) do
            self.chargeDens:accumulate(s:getCharge(), s:getNumDensity())
         end
         -- If not using linearized polarization term, set up laplacian weight.
         if not self.linearizedPolarization or (self._first and not self.uniformPolarization) then
            self.weight:clear(0.0)
            for nm, s in pairs(species) do
               if Species.GkSpecies.is(s) then
                  self.weight:accumulate(1.0, s:getPolarizationWeight(false))
               end
            end
            if self.ndim == 1 then
               self.modifierWeight:combine(self.kperp2, self.weight)
            else
               self.modifierWeight:clear(0.0)
               self.laplacianWeight:combine(-1.0, self.weight)
            end

            if self.adiabatic then
               self.modifierWeight:accumulate(1.0, self.adiabSpec:getQneutFac(false))
            end

            if self.ndim > 1 then
               self.phiSlvr:setLaplacianWeight(self.laplacianWeight)
            end
            if self.adiabatic or self.ndim == 1 then self.phiSlvr:setModifierWeight(self.modifierWeight) end
         end
         -- phi solve (elliptic, so update potCurr.phi).
         self.phiSlvr:advance(tCurr, {self.chargeDens}, {potCurr.phi})

         -- Apply BCs.
         local tmStart = Time.clock()
         potCurr.phi:sync(true)
         self.bcTime = self.bcTime + (Time.clock()-tmStart)
 
         self._first = false
      end
   else
      -- Just copy stuff over.
      if self.isElectromagnetic then 
         potRhs.apar:copy(potCurr.apar) 
      end
   end
end

-- Solve for dApardt in p>=2, or solve for a provisional dApardtProv in p=1.
function GkField:advanceStep2(tCurr, species, inIdx, outIdx)
   local potCurr = self:rkStepperFields()[inIdx]
   local potRhs  = self:rkStepperFields()[outIdx]

   local polyOrder = self.basis:polyOrder()

   if self.evolve then

      self.currentDens:clear(0.0)
      if self.ndim==1 then 
         self.modifierWeight:combine(self.kperp2/self.mu0, self.unitWeight) 
      else 
         self.modifierWeight:clear(0.0)
      end
      for nm, s in pairs(species) do
        if s:isEvolving() then 
           self.modifierWeight:accumulate(s:getCharge()*s:getCharge()/s:getMass(), s:getNumDensity())
           -- Taking momDensity at outIdx gives momentum moment of df/dt.
           self.currentDens:accumulate(s:getCharge(), s:getMomDensity(outIdx))
        end
      end
      self.dApardtSlvr:setModifierWeight(self.modifierWeight)
      -- dApar/dt solve.
      local dApardt = potCurr.dApardt
      self.dApardtSlvr:advance(tCurr, {self.currentDens}, {dApardt}) 
      
      -- Decrease effective polynomial order in z of dApar/dt by setting the highest order z coefficients to 0.
      -- This ensures that dApar/dt is in the same space as dPhi/dz.
      if self.ndim == 1 or self.ndim == 3 then -- Only have z direction in 1d or 3d (2d is assumed to be x,y).
         local localRange = dApardt:localRange()
         local indexer = dApardt:genIndexer()
         local ptr = dApardt:get(1)

         -- Loop over all cells
         for idx in localRange:rowMajorIter() do
            self.grid:setIndex(idx)
            
            dApardt:fill(indexer(idx), ptr)
            if self.ndim == 1 then
               ptr:data()[polyOrder] = 0.0
            else -- ndim == 3.
               if polyOrder == 1 then
                  ptr:data()[3] = 0.0
                  ptr:data()[5] = 0.0
                  ptr:data()[6] = 0.0
                  ptr:data()[7] = 0.0
               elseif polyOrder == 2 then
                  ptr:data()[9] = 0.0
                  ptr:data()[13] = 0.0
                  ptr:data()[14] = 0.0
                  ptr:data()[15] = 0.0
                  ptr:data()[16] = 0.0
                  ptr:data()[17] = 0.0
                  ptr:data()[18] = 0.0
                  ptr:data()[19] = 0.0
               end
            end
         end
      end

      -- Apply BCs.
      local tmStart = Time.clock()
      dApardt:sync(true)
      self.bcTime = self.bcTime + (Time.clock()-tmStart)

      if polyOrder > 1 then 
         -- Apar RHS is just dApar/dt.
         potRhs.apar:copy(dApardt)
      else 
         -- Save dApardt as dApardtProv, so that it can be used in upwinding 
         -- in vpar surface terms in p=1 Ohm's law and GK update.
         self.dApardtProv:copy(dApardt)
      end
   end
end

-- Note: step 3 is for p=1 only: solve for dApardt.
function GkField:advanceStep3(tCurr, species, inIdx, outIdx)
   local potCurr = self:rkStepperFields()[inIdx]
   local potRhs = self:rkStepperFields()[outIdx]

   local polyOrder = self.basis:polyOrder()

   if self.evolve then
      self.currentDens:clear(0.0)
      if self.ndim==1 then 
         self.modifierWeight:combine(self.kperp2/self.mu0, self.unitWeight) 
      else 
         self.modifierWeight:clear(0.0)
      end
      for nm, s in pairs(species) do
        if s:isEvolving() then 
           self.modifierWeight:accumulate(s:getCharge()*s:getCharge()/s:getMass(), s:getEmModifier())
           -- Taking momDensity at outIdx gives momentum moment of df/dt.
           self.currentDens:accumulate(s:getCharge(), s:getMomProjDensity(outIdx))
        end
      end
      self.dApardtSlvr2:setModifierWeight(self.modifierWeight)
      -- dApar/dt solve.
      local dApardt = potCurr.dApardt
      self.dApardtSlvr2:advance(tCurr, {self.currentDens}, {dApardt}) 
      
      -- Decrease effective polynomial order in z of dApar/dt by setting the highest order z coefficients to 0
      -- this ensures that dApar/dt is in the same space as dPhi/dz.
      if self.ndim == 1 or self.ndim == 3 then -- Only have z direction in 1d or 3d (2d is assumed to be x,y).
         local localRange = dApardt:localRange()
         local indexer = dApardt:genIndexer()
         local ptr = dApardt:get(1)

         -- Loop over all cells.
         for idx in localRange:rowMajorIter() do
            self.grid:setIndex(idx)
            
            dApardt:fill(indexer(idx), ptr)
            if self.ndim == 1 then
               ptr:data()[polyOrder] = 0.0
            else -- ndim == 3
               if polyOrder == 1 then
                  ptr:data()[3] = 0.0
                  ptr:data()[5] = 0.0
                  ptr:data()[6] = 0.0
                  ptr:data()[7] = 0.0
               elseif polyOrder == 2 then
                  ptr:data()[9] = 0.0
                  ptr:data()[13] = 0.0
                  ptr:data()[14] = 0.0
                  ptr:data()[15] = 0.0
                  ptr:data()[16] = 0.0
                  ptr:data()[17] = 0.0
                  ptr:data()[18] = 0.0
                  ptr:data()[19] = 0.0
               end
            end
         end
      end

      -- Apply BCs.
      local tmStart = Time.clock()
      dApardt:sync(true)
      self.bcTime = self.bcTime + (Time.clock()-tmStart)

      -- Apar RHS is just dApar/dt.
      potRhs.apar:copy(dApardt)
   end
end

function GkField:applyBcIdx(tCurr, idx)
   -- Don't do anything here. Global boundary conditions handled by solvers. 
   -- Syncs to update interproc ghost already done at end of advance steps.
end

-- NOTE: global boundary conditions handled by solver. this just updates interproc ghosts.
function GkField:applyBc(tCurr, potIn)
   local tmStart = Time.clock()
   potIn.phi:sync(true)
   if self.isElectromagnetic then 
     potIn.apar:sync(true) 
     potIn.dApardt:sync(true) 
   end
   self.bcTime = self.bcTime + (Time.clock()-tmStart)
end
   
function GkField:totalSolverTime()
   if self.phiSlvr then
     local time = self.phiSlvr.totalTime
     if self.isElectromagnetic and self.aparSlvr then time = time + self.aparSlvr.totalTime end
     if self.isElectromagnetic and self.dApardtSlvr then time = time + self.dApardtSlvr.totalTime end
     if self.isElectromagnetic and self.dApardtSlvr2 then time = time + self.dApardtSlvr2.totalTime end
     return time
   end
   return 0.0
end

function GkField:totalBcTime()
   return self.bcTime
end

function GkField:energyCalcTime()
   local t = self.int2Calc.totalTime
   if self.energyCalc then t = t + self.energyCalc.totalTime end
   return t
end

-- GkGeometry ---------------------------------------------------------------------
--
-- A field object with fields specifying the magnetic geometry for GK.
--------------------------------------------------------------------------------

local GkGeometry = Proto(FieldBase.FuncFieldBase)

-- Methods for no field object.
function GkGeometry:init(tbl)
   GkGeometry.super.init(self, tbl)
   self.tbl = tbl
end

function GkGeometry:fullInit(appTbl)
   local tbl = self.tbl -- previously store table.

   self.ioMethod = "MPI"
   self.evolve = xsys.pickBool(tbl.evolve, false) -- by default these fields are not time-dependent.

   -- Create triggers to write fields.
   if tbl.nFrame then
      self.ioTrigger = LinearTrigger(0, appTbl.tEnd, tbl.nFrame)
   else
      self.ioTrigger = LinearTrigger(0, appTbl.tEnd, appTbl.nFrame)
   end

   self.ioFrame = 0 -- Frame number for IO.
   
   -- Get function to initialize background magnetic field.
   self.bmagFunc = tbl.bmag
   --assert(self.bmagFunc and type(self.bmagFunc)=="function", "GkGeometry: must specify background magnetic field function with 'bmag'")

   -- For s-alpha geometry.
   self.salpha = tbl.salpha

   -- Wall potential for sheath BCs.
   self.phiWallFunc = tbl.phiWall
   if self.phiWallFunc then assert(type(self.phiWallFunc)=="function", "GkGeometry: phiWall must be a function (t, xn)") end
end

function GkGeometry:hasEB() end
function GkGeometry:setCfl() end
function GkGeometry:setIoMethod(ioMethod) self.ioMethod = ioMethod end
function GkGeometry:setBasis(basis) self.basis = basis end
function GkGeometry:setGrid(grid) self.grid = grid; self.ndim = self.grid:ndim() end

function GkGeometry:alloc()
   -- Allocate fields.
   self.geo = {}

   -- Background magnetic field.
   self.geo.bmag = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false,
   }

   -- bmagInv ~ 1/B.
   self.geo.bmagInv = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }

   -- bhat.grad z.
   self.geo.gradpar = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }

   -- Functions for magnetic drifts.
   -- bdriftX = 1/B*curl(bhat).grad x.
   self.geo.bdriftX = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }
   -- bdriftY = 1/B*curl(bhat).grad y.
   self.geo.bdriftY = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }
 
   -- Functions for Laplacian.
   -- gxx = |grad x|**2.
   self.geo.gxx = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }
   -- gxy = grad x . grad y.
   self.geo.gxy = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }
   -- gyy = |grad y|**2.
   self.geo.gyy = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }
   

   -- Jacobian of coordinate transformation.
   self.geo.jacobGeo = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }

   -- Wall potential for sheath BCs.
   self.geo.phiWall = DataStruct.Field {
      onGrid = self.grid,
      numComponents = self.basis:numBasis(),
      ghost = {1, 1},
      syncPeriodicDirs = false
   }
      
   -- Create Adios object for field I/O.
   self.fieldIo = AdiosCartFieldIo {
      elemType = self.geo.bmag:elemType(),
      method = self.ioMethod,
   }   
end

function GkGeometry:createSolver()

   if self.salpha then
      local salpha = self.salpha
      self.bmagFunc = function (t, xn)
         local x, y, z
         if self.ndim == 1 then z = xn[1]; x = assert(salpha.r0, "must set salpha.r0 for 1D (local limit) s-alpha cases") 
         elseif self.ndim == 2 then x, y, z = xn[1], xn[2], 0
         else x, y, z = xn[1], xn[2], xn[3]
         end
         return salpha.B0*salpha.R0/(salpha.R0 + x*math.cos(z))
      end
      self.bmagInvFunc = function (t, xn)
         return 1/self.bmagFunc(t, xn)
      end
      self.jacobGeoFunc = function (t, xn)
         if self.ndim == 2 then return 1 else return salpha.q*salpha.R0 end
      end
      self.bdriftXFunc = function (t, xn)
         local x, y, z
         if self.ndim == 1 then z = xn[1]
         elseif self.ndim == 2 then x, y, z = xn[1], xn[2], 0
         else x, y, z = xn[1], xn[2], xn[3]
         end
         return -math.sin(z)/(salpha.B0*salpha.R0)
      end
      self.bdriftYFunc = function (t, xn)
         local x, y, z
         if self.ndim == 1 then z = xn[1]
         elseif self.ndim == 2 then x, y, z = xn[1], xn[2], 0
         else x, y, z = xn[1], xn[2], xn[3]
         end
         return -(math.cos(z) + salpha.shat*z*math.sin(z))/(salpha.B0*salpha.R0)
      end
      self.gradparFunc = function (t, xn)
         return 1/(salpha.q*salpha.R0)
      end
      self.gxxFunc = function (t, xn)
         return 1
      end
      self.gxyFunc = function (t, xn)
         local x, y, z
         if self.ndim == 1 then z = xn[1]
         elseif self.ndim == 2 then x, y, z = xn[1], xn[2], 0
         else x, y, z = xn[1], xn[2], xn[3]
         end
         return salpha.shat*z
      end
      self.gyyFunc = function (t, xn)
         local x, y, z
         if self.ndim == 1 then z = xn[1]
         elseif self.ndim == 2 then x, y, z = xn[1], xn[2], 0
         else x, y, z = xn[1], xn[2], xn[3]
         end
         return 1 + (salpha.shat*z)^2
      end
   else
      -- Calculate 1/B function.
      self.bmagInvFunc = function (t, xn)
         return 1/self.bmagFunc(t,xn)
      end
      -- Calculate magnetic drift functions.
      if self.ndim > 1 then
         local function bgrad(xn)
            local function bmagUnpack(...)
               local xn1 = {...}
               return self.bmagFunc(0, xn1)
            end
            local deriv = diff.derivativef(bmagUnpack, #xn)
            local xntable = {}
            for i = 1, #xn do
              xntable[i] = xn[i]
            end
            local f, dx, dy, dz = deriv(unpack(xntable))
            return dx, dy, dz
         end
         self.bdriftXFunc = function (t, xn)
            local bgradX, bgradY, bgradZ = bgrad(xn)
            return -bgradY/self.bmagFunc(t,xn)^2
         end
         self.bdriftYFunc = function (t, xn)
            local bgradX, bgradY, bgradZ = bgrad(xn)
            return bgradX/self.bmagFunc(t,xn)^2
         end
      end
      self.gxxFunc = function (t, xn)
         return 1.0
      end
      self.gxyFunc = function (t, xn)
         return 0.0
      end
      self.gyyFunc = function (t, xn)
         return 1.0
      end
   end

   -- Projection updaters.
   self.setBmag = Updater.ProjectOnBasis {
      onGrid          = self.grid,
      basis           = self.basis,
      evaluate        = self.bmagFunc,
      projectOnGhosts = true,
   }
   self.setBmagInv = Updater.ProjectOnBasis {
      onGrid          = self.grid,
      basis           = self.basis,
      projectOnGhosts = true,
      evaluate        = self.bmagInvFunc
   }
   if self.gradparFunc then 
      self.setGradpar = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.gradparFunc
      }
   else
      self.setGradpar = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = function(t, xn) return 1.0 end
      }
   end
   if self.jacobGeoFunc then 
      self.setJacobGeo = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.jacobGeoFunc
      }
   else 
      self.setJacobGeo = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = function(t, xn) return 1.0 end
      }
   end
   if self.gxxFunc then 
      self.setGxx = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.gxxFunc
      }
   else 
      self.setGxx = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = function(t, xn) return 1.0 end
      }
   end
   if self.gxyFunc then 
      self.setGxy = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.gxyFunc
      }
   else 
      self.setGxy = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = function(t, xn) return 0.0 end
      }
   end
   if self.gyyFunc then 
      self.setGyy = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.gyyFunc
      }
   else 
      self.setGyy = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = function(t, xn) return 1.0 end
      }
   end
   if self.bdriftXFunc then 
      self.setBdriftX = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.bdriftXFunc
      }
   end
   if self.bdriftYFunc then
      self.setBdriftY = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.bdriftYFunc
      }
   end
   if self.phiWallFunc then 
      self.setPhiWall = Updater.ProjectOnBasis {
         onGrid          = self.grid,
         basis           = self.basis,
         projectOnGhosts = true,
         evaluate        = self.phiWallFunc
      }
   end

   -- Determine which variables bmag depends on by checking if setting a variable to nan results in nan.
   local ones = {}
   for dir = 1, self.ndim do
      ones[dir] = 1
   end
   self.bmagVars = {}
   for dir = 1, self.ndim do
      ones[dir] = 0/0 -- Set this var to nan.
      -- Test if result is nan.. nan is the only value that doesn't equal itself.
      if self.bmagFunc(0, ones) ~= self.bmagFunc(0, ones) then 
        -- If result is nan, bmag must depend on this var.
        table.insert(self.bmagVars, dir) 
      end
      ones[dir] = 1 -- Reset so we can check other vars.
   end
   if self.bmagVars[1] == nil then self.bmagVars[1] = 0 end
end

function GkGeometry:createDiagnostics()
end

function GkGeometry:initField()
   self.setBmag:advance(0.0, {}, {self.geo.bmag})
   self.setBmagInv:advance(0.0, {}, {self.geo.bmagInv})
   if self.setGradpar then self.setGradpar:advance(0.0, {}, {self.geo.gradpar})
   else self.geo.gradpar:clear(0.0) end
   if self.setJacobGeo then self.setJacobGeo:advance(0.0, {}, {self.geo.jacobGeo})
   else self.geo.jacobGeo:clear(0.0) end
   if self.setGxx then self.setGxx:advance(0.0, {}, {self.geo.gxx}) end
   if self.setGxy then self.setGxy:advance(0.0, {}, {self.geo.gxy}) end
   if self.setGyy then self.setGyy:advance(0.0, {}, {self.geo.gyy}) end
   if self.setBdriftX then self.setBdriftX:advance(0.0, {}, {self.geo.bdriftX})
   else self.geo.bdriftX:clear(0.0) end
   if self.setBdriftY then self.setBdriftY:advance(0.0, {}, {self.geo.bdriftY})
   else self.geo.bdriftY:clear(0.0) end
   if self.setPhiWall then self.setPhiWall:advance(0.0, {}, {self.geo.phiWall})
   else self.geo.phiWall:clear(0.0) end

   -- Sync ghost cells. these calls do not enforce periodicity because
   -- These fields initialized with syncPeriodicDirs = false.
   self.geo.bmag:sync(false)
   self.geo.bmagInv:sync(false)
   self.geo.gradpar:sync(false)
   self.geo.gxx:sync(false)
   self.geo.gxy:sync(false)
   self.geo.gyy:sync(false)
   self.geo.jacobGeo:sync(false)
   self.geo.bdriftX:sync(false)
   self.geo.bdriftY:sync(false)
   self.geo.phiWall:sync(false)

   -- Apply BCs.
   self:applyBc(0, self.geo)
end

function GkGeometry:write(tm)
   -- Not evolving geometry, so only write geometry at beginning.
   if self.ioFrame == 0 then
      self.fieldIo:write(self.geo.bmag, string.format("bmag_%d.bp", self.ioFrame), tm, self.ioFrame)
      if self.setBdriftX then
	 self.fieldIo:write(self.geo.bdriftX, string.format("bdriftX_%d.bp", self.ioFrame), tm, self.ioFrame)
      end
      if self.setBdriftY then
	 self.fieldIo:write(self.geo.bdriftY, string.format("bdriftY_%d.bp", self.ioFrame), tm, self.ioFrame)
      end
      if self.setGradpar then
	 self.fieldIo:write(self.geo.gradpar, string.format("gradpar_%d.bp", self.ioFrame), tm, self.ioFrame)
      end
   end
   self.ioFrame = self.ioFrame+1
end

function GkGeometry:writeRestart(tm)
end

function GkGeometry:rkStepperFields()
   return { self.geo, self.geo, self.geo, self.geo }
end

function GkGeometry:advance(tCurr)
   if self.evolve then 
      self.setPhiWall:advance(tCurr, {}, self.geo.phiWall)
   end 
end

function GkGeometry:applyBcIdx(tCurr, idx)
   self:applyBc(tCurr, self:rkStepperFields()[1])
end

function GkGeometry:applyBc(tCurr, geoIn)
   if self.evolve then 
      geoIn.phiWall:sync(false)
   end
end

function GkGeometry:totalSolverTime()
   if self.evolve then return self.setPhiWall.totalTime
   else return 0 end
end

function GkGeometry:totalBcTime() return 0.0 end
function GkGeometry:energyCalcTime() return 0.0 end


return {GkField = GkField, GkGeometry = GkGeometry}
