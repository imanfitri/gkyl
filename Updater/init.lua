-- Gkyl ------------------------------------------------------------------------
--
-- Dispatch into the updater modules
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

-- Gkyl modules
local Bc = require "Updater.Bc"
local StairSteppedBc = require "Updater.StairSteppedBc"
local BgkCollisions = require "Updater.BgkCollisions"
local CartFieldBinOp = require "Updater.CartFieldBinOp"
local CartFieldIntegratedQuantCalc = require "Updater.CartFieldIntegratedQuantCalc"
local ConfToPhase = require "Updater.ConfToPhase"
local DistFuncIntegratedMomentCalc = require "Updater.DistFuncIntegratedMomentCalc"
local DistFuncMomentCalc = require "Updater.DistFuncMomentCalc"
local EvalOnNodes = require "Updater.EvalOnNodes"
local FemGyroaverage = require "Updater.FemGyroaverage"
local FemParPoisson = require "Updater.FemParPoisson"
local FemPerpPoisson = require "Updater.FemPerpPoisson"
local FemPoisson = require "Updater.FemPoisson"
local FiveMomentSrc = require "Updater.FiveMomentSrc"
local TenMomentSrc = require "Updater.TenMomentSrc"
local TenMomentRelax = require "Updater.TenMomentRelax"
local HyperDisCont = require "Updater.HyperDisCont"
local HyperDisContCellBased = require "Updater.HyperDisContCellBased"
local LagrangeFix = require "Updater.LagrangeFix"
local MappedPoisson = require "Updater.MappedPoisson"
local MaxwellianOnBasis = require "Updater.MaxwellianOnBasis"
local PositivityCheck = require "Updater.PositivityCheck"
local PositivityRescale = require "Updater.PositivityRescale"
local ProjectOnBasis = require "Updater.ProjectOnBasis"
local SelfPrimMoments = require "Updater.SelfPrimMoments"
local CrossPrimMoments = require "Updater.CrossPrimMoments"
local SolidSurface = require "Updater.SolidSurface"
local SpitzerCollisionality = require "Updater.SpitzerCollisionality"
local VoronovIonization = require "Updater.VoronovIonization"
local WavePropagation = require "Updater.WavePropagation"

return {
   Bc = Bc,
   StairSteppedBc = StairSteppedBc,
   BgkCollisions = BgkCollisions,
   CartFieldBinOp = CartFieldBinOp,
   CartFieldIntegratedQuantCalc = CartFieldIntegratedQuantCalc,
   ConfToPhase = ConfToPhase,
   DistFuncIntegratedMomentCalc = DistFuncIntegratedMomentCalc,
   DistFuncMomentCalc = DistFuncMomentCalc,
   EvalOnNodes = EvalOnNodes,
   FemGyroaverage = FemGyroaverage,
   FemParPoisson = FemParPoisson,
   FemPerpPoisson = FemPerpPoisson,
   FemPoisson = FemPoisson,
   FiveMomentSrc = FiveMomentSrc,
   TenMomentSrc = TenMomentSrc,
   TenMomentRelax = TenMomentRelax,
   HyperDisCont = HyperDisCont,
   HyperDisContCellBased = HyperDisContCellBased,
   LagrangeFix = LagrangeFix,
   MappedPoisson = MappedPoisson,
   MaxwellianOnBasis = MaxwellianOnBasis,
   PositivityCheck = PositivityCheck,
   PositivityRescale = PositivityRescale,
   ProjectOnBasis = ProjectOnBasis,
   SelfPrimMoments = SelfPrimMoments,
   CrossPrimMoments = CrossPrimMoments,
   SolidSurface = SolidSurface,
   SpitzerCollisionality = SpitzerCollisionality,
   VoronovIonization = VoronovIonization,
   WavePropagation = WavePropagation,
}
