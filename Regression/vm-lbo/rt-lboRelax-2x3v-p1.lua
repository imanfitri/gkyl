-- Gkyl ------------------------------------------------------------------------
--
--
local Plasma = require("App.PlasmaOnCartGrid").VlasovMaxwell

-- This test relaxes a rectangular/square IC and a bump in tail IC.
-- Maxwellian's for comparison with each are also created.

polyOrder = 1
nu        = 0.01                            -- Collision frequency.
n0        = 1.0                             -- Density.
u0        = {0.0,0.0,0.0}                   -- Flow speed.
vMin      = -2.0                            -- Min velocity in grid.
vMax      =  2.0                            -- Max velocity in grid.
Nx        = {2,2}                           -- Number of cells in configuration space.
Nv        = {16,16,16}                      -- Number of cells in velocity space.
-- The next three are for p1, v\in[-2,2], 2x16, rectangular IC.
nMr  = 1.0                                  -- Density of Maxwellian and rectangle. 
uMr  = {0.0,0.0,0.0}                        -- Flow speed of Maxwellian and rectangle. 
vtMr = math.sqrt(0.0208333333+3.333e-11)    -- Thermal speed of Maxwellian and rectangle.
-- Large bump on tail of Maxwellian:
vt   = math.sqrt(1.0/24.0)                  -- Thermal speed of Maxwellian in bump.
ab   = 4*math.sqrt(0.1)                     -- Amplitude of bump.
ub   = {2*math.sqrt(1/3),0.0,0.0}           -- Location of bump.
sb   = 0.12                                 -- Softening factor to avoid divergence.
vtb  = 1.0/math.sqrt(2.0)                   -- Thermal speed of Maxwellian in bump.
-- These are for p1, v\in[-2,2], 2x16, bump in tail IC. 
nMb  = 3.356702993+2.9312e-12               -- Density of Maxwellian and bump. 
uMb  = {0.51706459056+3.253e-12,0.0,0.0}    -- Flow speed of Maxwellian and bump. 
vtMb = math.sqrt(0.2394147396+8.02e-11)     -- Thermal speed of Maxwellian and bump.

-- Top hat function without drift (u=0).
local function topHat(x, y, vx, vy, vz, n, ux, uy, uz, vth)
   local fOut   = 0.0
   local v0     = math.sqrt(3.0*(vth^2)/2.0)
   if (math.abs(vx) <= v0) and (math.abs(vy) <= v0) and (math.abs(vz) <= v0) then
      fOut = n/((2.0*v0)^2)
   else
      fOut = 0.0
   end
   return fOut
end

-- Maxwellian with a Maxwellian bump in the tail.
local function bumpMaxwell(x,y,vx,vy,vz,n,ux,uy,uz,vth,bA,bUx,bUy,bUz,bS,bVth)
   local Pi   = math.pi
   local vSq  = ((vx-ux)^2+(vy-uy)^2+(vz-uz)^2)/((math.sqrt(2.0)*vth)^2)
   local vbSq = ((vx-ux)^2+(vy-uy)^2+(vz-uz)^2)/((math.sqrt(2.0)*bVth)^2)

   return (n/math.sqrt((2.0*Pi*(vth^2))^3))*math.exp(-vSq)
         +(n/math.sqrt((2.0*Pi*(bVth^2))^3))*math.exp(-vbSq)*(bA^2)/((vx-bUx)^2+(vy-bUy)^2+(vz-bUz)^2+bS^2)
end

plasmaApp = Plasma.App {
   logToFile = false,

   tEnd        = 1.0,           -- End time.
   nFrame      = 1,             -- Number of frames to write.
   lower       = {0.0,0.0},     -- Configuration space lower coordinate.
   upper       = {1.0,1.0},     -- Configuration space upper coordinate.
   cells       = Nx,            -- Configuration space cells.
   basis       = "serendipity", -- One of "serendipity" or "maximal-order".
   polyOrder   = polyOrder,     -- Polynomial order.
   timeStepper = "rk3",         -- One of "rk2", "rk3" or "rk3s4".

   -- Decomposition for configuration space.
   decompCuts = {1,1},        -- Cuts in each configuration direction.
   useShared  = false,          -- If to use shared memory.

   -- Boundary conditions for configuration space.
   periodicDirs = {1,2},      -- Periodic directions.

   -- Neutral species with a rectangular/square IC.
   square = Plasma.Species {
      charge = 0.0, mass = 1.0,
      -- Velocity space grid.
      lower      = {vMin,vMin,vMin},
      upper      = {vMax,vMax,vMax},
      cells      = Nv,
      -- Initial conditions.
      init = function (t, xn)
	 local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]

         return topHat(x, y, vx, vy, vz, n0, u0[1], u0[2], u0[3], vt)
      end,
      -- Evolve species?
      evolve = true,
      -- Diagnostic moments.
      diagnosticMoments = { "M0", "M1i", "M2" },
      -- Collisions.
      coll = Plasma.LBOCollisions {
         collideWith = {'square'},
         frequencies = {nu},
      },
   },

  -- -- Maxwellian for comparison with rectangular IC.
  -- maxwellSquare = Plasma.Species {
  --    charge = 0.0, mass = 1.0,
  --    -- Velocity space grid.
  --    lower      = {vMin,vMin,vMin},
  --    upper      = {vMax,vMax,vMax},
  --    cells      = Nv,
  --    -- Initial conditions.
  --    init = Plasma.MaxwellianProjection {
  --       density         = nMr,
  --       driftSpeed      = {uMr,0.0,0.0},
  --       temperature     = vtMr^2,
  --       exactScaleM0    = false,
  --       exactLagFixM012 = true,
  --    },
  --    -- Evolve species?
  --    evolve = false,
  --    -- Diagnostic moments.
  --    diagnosticMoments = { "M0", "M1i", "M2" },
  -- },

   -- Neutral species with a bump in the tail.
   bump = Plasma.Species {
      charge = 0.0, mass = 1.0,
      -- Velocity space grid.
      lower      = {vMin,vMin,vMin},
      upper      = {vMax,vMax,vMax},
      cells      = Nv,
      -- Initial conditions.
      init = function (t, xn)
         local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]

         return bumpMaxwell(x,y,vx,vy,vz,n0,u0[1],u0[2],u0[3],vt,ab,ub[1],ub[2],ub[3],sb,vtb)
      end,
      -- Evolve species?
      evolve = true,
      -- Diagnostic moments.
      diagnosticMoments = { "M0", "M1i", "M2" },
      -- Collisions.
      coll = Plasma.LBOCollisions {
         collideWith = {'bump'},
         frequencies = {nu},
      },
   },

  -- -- Maxwellian for comparison with bump in tail IC.
  -- maxwellBump = Plasma.Species {
  --    charge = 0.0, mass = 1.0,
  --    -- Velocity space grid.
  --    lower      = {vMin,vMin,vMin},
  --    upper      = {vMax,vMax,vMax},
  --    cells      = Nv,
  --    -- Initial conditions.
  --    init = Plasma.MaxwellianProjection {
  --       density         = nMb,
  --       driftSpeed      = {uMb,0.0,0.0},
  --       temperature     = vtMb^2,
  --       exactScaleM0    = false,
  --       exactLagFixM012 = true,
  --    },
  --    -- Evolve species?
  --    evolve = false,
  --    -- Diagnostic moments.
  --    diagnosticMoments = { "M0", "M1i", "M2" },
  -- },

}
-- run application
plasmaApp:run()
