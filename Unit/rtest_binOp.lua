-- Gkyl ------------------------------------------------------------------------
--
-- Tests for weak multiplication and division binary operations.
-- Here we use the calculation of primitive moments as a test case.
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

local Unit           = require "Unit"
local Grid           = require "Grid"
local DataStruct     = require "DataStruct"
local Basis          = require "Basis"
local Updater        = require "Updater"
local Lin            = require "Lib.Linalg"

local assert_equal = Unit.assert_equal
local assert_close = Unit.assert_close
local stats        = Unit.stats

------------------------------------------------------------------------------------
---                    Test in 1x
--- * Test weak division of a scalar 1x field by a scalar 1x field.
--- * Test weak multiplication of a scalar 1x field by a scalar 1x field.
--- * Test dot product of 1D vector fields.
------------------------------------------------------------------------------------
function test_binOp1x(nx, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local confGrid = Grid.RectCart {
      lower = {0.0},
      upper = {1.0},
      cells = {nx},
   }
   -- Basis functions.
   local basis = Basis.CartModalSerendipity { ndim = 1, polyOrder = p }
   io.write("nx=",nx," polyOrder=", p, "\n")

   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   -- Calculated and analytic dot momentum squared.
   local mom1Sq = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1SqA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }

   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
                    return math.exp(-x)
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   local initMom1Sqi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local x = xn[1]
                    return ((math.exp(-x))*math.sin(4.0*2.0*math.pi*x))^2
                 end
   }
   initMom1Sqi:advance(0.,{},{mom1SqA})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})

   -- Compute flow speed.
   local calcUi = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "Divide",
   }

   print("Computing flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")

   local calcMom1 = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")

   local confDotProduct = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "DotProduct",
   }
   print("Computing momentum squared...")
   local t1 = os.clock()
   confDotProduct:advance(0.,{mom1,mom1},{mom1Sq})
   local t2 = os.clock()
   io.write("Mom1Sq computation took total of ", t2-t1, " s\n")

   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1Sq = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }

   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)
   errMom1Sq:combine(1.0, mom1SqA, -1.0, mom1Sq)

   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   mom1SqA:write("mom1SqA.bp", 0.0)
   mom1Sq:write("mom1Sq.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = basis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1]), "\n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1]), "\n")

   local dynVecMom1Sq = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1Sq}, {dynVecMom1Sq})
   local tmMom1Sq, lvMom1Sq = dynVecMom1Sq:lastData()
   io.write("Average RMS in Mom1Sq error = ", math.sqrt(lvMom1Sq[1]), "\n")
   print()
   return math.sqrt(lvUi[1]), math.sqrt(lvMom1[1]), math.sqrt(lvMom1Sq[1])
end

------------------------------------------------------------------------------------
---                    Test in 2x
--- * Test weak division of a scalar 2x field by a scalar 2x field.
--- * Test weak multiplication of a scalar 2x field by a scalar 2x field.
--- * Test weak division of a 2D vector in 2x by a scalar 2x field.
--- * Test weak multiplication of a 2D vector in 2x by a scalar 2x field.
--- * Test dot product of a 2D vector field with itself.
--- * Test dot product of two different 2D vector fields.
------------------------------------------------------------------------------------
function test_binOp2x(nx, ny, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local confGrid = Grid.RectCart {
      lower = {0.0, 0.0},
      upper = {1.0, 1.0},
      cells = {nx, ny},
   }
   -- Basis functions.
   local basis = Basis.CartModalSerendipity { ndim = 2, polyOrder = p }
   io.write("nx=",nx," ny=",ny," polyOrder=", p, "\n")

   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*2,
      ghost         = {1, 1},
   }
   local mom12D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*2,
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local Ui2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*2,
      ghost         = {1, 1},
   }
   local UiA2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*2,
      ghost         = {1, 1},
   }
   -- Calculated and analytic speed squared and
   -- kinetic energy.
   local Usq = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local UsqA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local Ke = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local KeA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }

   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu   = 0.5
                    local sig  = 0.04
                    local x, y = xn[1], xn[2]
                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)*
                           math.exp(-((y-mu)/(math.sqrt(2)*sig))^2))+0.1
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y = xn[1], xn[2]
                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)*
                           math.exp(-((y-mu)/(math.sqrt(2)*sig))^2))+0.1
--                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                    return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x)
--                    return math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*
--                           math.sin(4.0*2.0*math.pi*x)  
                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   local initMom1i2D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y = xn[1], xn[2]
                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)*
                            math.exp(-((y-mu)/(math.sqrt(2)*sig))^2))+0.1, 
                          -(math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)*
                            math.exp(-((y-mu)/(math.sqrt(2)*sig))^2))-0.1 
--                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                    return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x)
--                    return math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*
--                           math.sin(4.0*2.0*math.pi*x)  
                 end
   }
   initMom1i2D:advance(0.,{},{mom1A2D})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y = xn[1], xn[2]
                    return 1.0
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
--                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})
   -- Analytic 2D flow velocity.
   local initUi2D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y = xn[1], xn[2]
                    return 1.0, -1.0
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
--                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi2D:advance(0.,{},{UiA2D})
   -- Analytic flow speed squared.
   local initUsq = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local x, y = xn[1], xn[2]
                    return 2.0
                 end
   }
   initUsq:advance(0.,{},{UsqA})
   -- Analytic kinetic energy.
   local initKe = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local x, y = xn[1], xn[2]
                    local mu  = 0.5
                    local sig = 0.04
                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)*
                            math.exp(-((y-mu)/(math.sqrt(2)*sig))^2))+0.1
                          +(math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)*
                            math.exp(-((y-mu)/(math.sqrt(2)*sig))^2))+0.1 
                 end
   }
   initKe:advance(0.,{},{KeA})

   -- Compute flow speed.
   local calcUi = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "Divide",
   }

   print("Computing flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")
   print("Computing 2D flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A2D},{Ui2D})
   local t2 = os.clock()
   io.write("Ui2D computation took total of ", t2-t1, " s\n")

   local calcMom1 = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")
   print("Computing 2D momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA2D},{mom12D})
   local t2 = os.clock()
   io.write("Mom12D computation took total of ", t2-t1, " s\n")

   local confDotProduct = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "DotProduct",
   }
   print("Computing speed squared...")
   local t1 = os.clock()
   confDotProduct:advance(0.,{UiA2D,UiA2D},{Usq})
   local t2 = os.clock()
   io.write("Usq computation took total of ", t2-t1, " s\n")
   print("Computing kinetic energy...")
   local t1 = os.clock()
   confDotProduct:advance(0.,{UiA2D,mom1A2D},{Ke})
   local t2 = os.clock()
   io.write("Ke computation took total of ", t2-t1, " s\n")

   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errU2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*2,
      ghost = {1, 1}
   }
   local errMom12D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*2,
      ghost = {1, 1}
   }
   local errUsq = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errKe = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }

   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)
   errU2D:combine(1.0, UiA2D, -1.0, Ui2D)
   errMom12D:combine(1.0, mom1A2D, -1.0, mom12D)
   errUsq:combine(1.0, UsqA, -1.0, Usq)
   errKe:combine(1.0, KeA, -1.0, Ke)

   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)
   mom1A2D:write("mom1A2D.bp", 0.0)
   mom12D:write("mom12D.bp", 0.0)
   Ui2D:write("Ui2D.bp", 0.0)
   UiA2D:write("UiA2D.bp", 0.0)
   Usq:write("Usq.bp", 0.0)
   UsqA:write("UsqA.bp", 0.0)
   Ke:write("Ke.bp", 0.0)
   KeA:write("KeA.bp", 0.0)

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = basis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1]), "\n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1]), "\n")

   local calcInt2D = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = basis,
      numComponents = 2,
      quantity      = "V2"
   }
   local dynVecUi2D = DataStruct.DynVector { numComponents = 2 }
   calcInt2D:advance(0.0, {errU2D}, {dynVecUi2D})
   local tmUi2D, lvUi2D = dynVecUi2D:lastData()
   io.write("Average RMS in Ui2D error = (", math.sqrt(lvUi2D[1]),",", math.sqrt(lvUi2D[2]),") \n")

   local dynVecMom12D = DataStruct.DynVector { numComponents = 2 }
   calcInt2D:advance(0.0, {errMom12D}, {dynVecMom12D})
   local tmMom12D, lvMom12D = dynVecMom12D:lastData()
   io.write("Average RMS in Mom12D error = (", math.sqrt(lvMom12D[1]),",", math.sqrt(lvMom12D[2]),") \n")

   local dynVecUsq = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errUsq}, {dynVecUsq})
   local tmUsq, lvUsq = dynVecUsq:lastData()
   io.write("Average RMS in Usq error = ", math.sqrt(lvUsq[1]), "\n")
   local dynVecKe = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errKe}, {dynVecKe})
   local tmKe, lvKe = dynVecKe:lastData()
   io.write("Average RMS in Ke error = ", math.sqrt(lvKe[1]), "\n")
   print()
   return math.sqrt(lvUi[1]), math.sqrt(lvMom1[1]), math.sqrt(lvUi2D[1]), math.sqrt(lvMom12D[1]), 
          math.sqrt(lvUi2D[2]), math.sqrt(lvMom12D[2]), math.sqrt(lvUsq[1]), math.sqrt(lvKe[1])
end

------------------------------------------------------------------------------------
---                    Test in 3x
--- * Test weak division of a scalar 3x field by a scalar 3x field.
--- * Test weak multiplication of a scalar 3x field by a scalar 3x field.
--- * Test weak division of a 3D vector in 3x by a scalar 3x field.
--- * Test weak multiplication of a 3D vector in 3x by a scalar 3x field.
--- * Test dot product of a 3D vector field with itself.
--- * Test dot product of two different 3D vector fields.
-- 
------------------------------------------------------------------------------------
function test_binOp3x(nx, ny, nz, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local confGrid = Grid.RectCart {
      lower = {0.0, 0.0, 1.0},
      upper = {1.0, 1.0, 1.0},
      cells = {nx, ny, nz},
   }
   -- Basis functions.
   local basis = Basis.CartModalSerendipity { ndim = 3, polyOrder = p }
   io.write("nx=",nx," ny=",ny," nz=",nz," polyOrder=", p, "\n")

   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*3,
      ghost         = {1, 1},
   }
   local mom13D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*3,
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local Ui3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*3,
      ghost         = {1, 1},
   }
   local UiA3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*3,
      ghost         = {1, 1},
   }
   -- Calculated and analytic speed squared
   -- and kinetic energy.
   local Usq = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local UsqA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local Ke = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }
   local KeA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost         = {1, 1},
   }

   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu   = 0.5
                    local sig  = 0.04
                    local x, y, z = xn[1], xn[2], xn[3]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
                    return math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0)
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z = xn[1], xn[2], xn[3]
--                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                    return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x)
                    return math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0)*
                           math.sin(4.0*2.0*math.pi*x)  
                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   local initMom1i3D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z = xn[1], xn[2], xn[3]
--                    return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                    return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x)
                    return math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0)*
                           math.sin(4.0*2.0*math.pi*x),  
                           math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0),
                          -math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0)
                 end
   }
   initMom1i3D:advance(0.,{},{mom1A3D})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z = xn[1], xn[2], xn[3]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})
   local initUi3D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z = xn[1], xn[2], xn[3]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x), 1.0, -1.0
                 end
   }
   initUi3D:advance(0.,{},{UiA3D})
   -- Analytic squared speed.
   local initUsq = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z = xn[1], xn[2], xn[3]
                    return (math.sin(4.0*2.0*math.pi*x))^2+1.0+1.0
                 end
   }
   initUsq:advance(0.,{},{UsqA})
   -- Analytic kinetic energy.
   local initKe = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = basis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z = xn[1], xn[2], xn[3]
                    return math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0)*
                           math.sin(4.0*2.0*math.pi*x)*math.sin(4.0*2.0*math.pi*x)  
                          +math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0)
                          +math.exp(-x)*math.exp(-((y-mu)/(math.sqrt(2)*sig))^2)*(math.tanh(z)+3.0)
                 end
   }
   initKe:advance(0.,{},{KeA})

   -- Compute flow speed.
   local calcUi = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "Divide",
   }

   print("Computing flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")
   print("Computing 3D flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A3D},{Ui3D})
   local t2 = os.clock()
   io.write("Ui3D computation took total of ", t2-t1, " s\n")

   local calcMom1 = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")
   print("Computing 3D momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA3D},{mom13D})
   local t2 = os.clock()
   io.write("Mom13D computation took total of ", t2-t1, " s\n")

   local confDotProduct = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = basis,
      operation  = "DotProduct",
   }
   print("Computing squared speed...")
   local t1 = os.clock()
   confDotProduct:advance(0.,{UiA3D,UiA3D},{Usq})
   local t2 = os.clock()
   io.write("Usq computation took total of ", t2-t1, " s\n")
   print("Computing kinetic energy...")
   local t1 = os.clock()
   confDotProduct:advance(0.,{UiA3D,mom1A3D},{Ke})
   local t2 = os.clock()
   io.write("Ke computation took total of ", t2-t1, " s\n")

   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errU3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*3,
      ghost = {1, 1}
   }
   local errMom13D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis()*3,
      ghost = {1, 1}
   }
   local errUsq = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }
   local errKe = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = basis:numBasis(),
      ghost = {1, 1}
   }

   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)
   errU3D:combine(1.0, UiA3D, -1.0, Ui3D)
   errMom13D:combine(1.0, mom1A3D, -1.0, mom13D)
   errUsq:combine(1.0, UsqA, -1.0, Usq)
   errKe:combine(1.0, KeA, -1.0, Ke)

   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)
   mom1A3D:write("mom1A3D.bp", 0.0)
   mom13D:write("mom13D.bp", 0.0)
   Ui3D:write("Ui3D.bp", 0.0)
   UiA3D:write("UiA3D.bp", 0.0)
   Usq:write("Usq.bp", 0.0)
   UsqA:write("UsqA.bp", 0.0)
   Ke:write("Ke.bp", 0.0)
   KeA:write("KeA.bp", 0.0)

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = basis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1]), "\n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1]), "\n")

   local calcInt3D = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = basis,
      numComponents = 3,
      quantity      = "V2"
   }
   local dynVecUi3D = DataStruct.DynVector { numComponents = 3 }
   calcInt3D:advance(0.0, {errU3D}, {dynVecUi3D})
   local tmUi3D, lvUi3D = dynVecUi3D:lastData()
   io.write("Average RMS in Ui3D error = (", math.sqrt(lvUi3D[1]),",", math.sqrt(lvUi3D[2]),",", math.sqrt(lvUi3D[3]),") \n")

   local dynVecMom13D = DataStruct.DynVector { numComponents = 3 }
   calcInt3D:advance(0.0, {errMom13D}, {dynVecMom13D})
   local tmMom13D, lvMom13D = dynVecMom1:lastData()
   io.write("Average RMS in Mom13D error = (", math.sqrt(lvMom13D[1]),",", math.sqrt(lvMom13D[2]),",", math.sqrt(lvMom13D[3]),") \n")

   local dynVecUsq = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errUsq}, {dynVecUsq})
   local tmUsq, lvUsq = dynVecUsq:lastData()
   io.write("Average RMS in Usq error = ", math.sqrt(lvUsq[1]), "\n")
   local dynVecKe = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errKe}, {dynVecKe})
   local tmKe, lvKe = dynVecKe:lastData()
   io.write("Average RMS in Ke error = ", math.sqrt(lvKe[1]), "\n")

   print()
   return math.sqrt(lvUi[1]), math.sqrt(lvMom1[1]), math.sqrt(lvUi3D[1]), math.sqrt(lvMom13D[1]), 
          math.sqrt(lvUi3D[2]), math.sqrt(lvMom13D[2]), math.sqrt(lvUi3D[3]), math.sqrt(lvMom13D[3]),
          math.sqrt(lvUsq[1]), math.sqrt(lvKe[1])
end

------------------------------------------------------------------------------------
---                    Test in 1x1v
--- * Test weak division of a scalar 1x field by a scalar 1x field.
--- * Test weak multiplication of a scalar 1x field by a scalar 1x field.
--- * Test weak multiplication of a 1x1v scalar field by a scalar 1x field.
------------------------------------------------------------------------------------
function test_binOp1x1v(nx, nv, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local phaseGrid = Grid.RectCart {
      lower = {0.0, -6.0},
      upper = {1.0, 6.0},
      cells = {nx, nv},
   }
   local confGrid = Grid.RectCart {
      lower = { phaseGrid:lower(1) },
      upper = { phaseGrid:upper(1) },
      cells = { phaseGrid:numCells(1) },
   }
   -- Basis functions.
   local phaseBasis = Basis.CartModalSerendipity { ndim = 2, polyOrder = p }
   local confBasis  = Basis.CartModalSerendipity { ndim = 1, polyOrder = p }
   io.write("nx=",nx," nv=",nv," polyOrder=", p, "\n")

   -- Phase space distribution function.
   local distF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Analytic and calculated numDens*distF.
   local ndistF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   local ndistFA = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }

   -- Initialize distribution function. We will (weak) multiply this by numDens.
   local initDistF = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muV  = 0.0
                    local sigV = 0.8
                    local x, v = xn[1], xn[2]
                    return math.exp(-((v-muV)/(math.sqrt(2)*sigV))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initDistF:advance(0.,{},{distF})
   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
                    return math.exp(-x)
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   -- Analytic numDens*distF.
   local initnDistFA = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muV  = 0.0
                    local sigV = 0.8
                    local x, v = xn[1], xn[2]
                    return math.exp(-x)*math.exp(-((v-muV)/(math.sqrt(2)*sigV))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initnDistFA:advance(0.,{},{ndistFA})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})

   -- Compute flow speed.
   local fldDiv = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Divide",
   }

   print("Computing flow speed...")
   local t1 = os.clock()
   fldDiv:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")

   local fldMult = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   fldMult:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")

   -- Multiply distribution function by number density.
   local pfldMult = Updater.CartFieldBinOp {
      onGrid     = phaseGrid,
      weakBasis  = phaseBasis,
      fieldBasis = confBasis,
      operation  = "Multiply",
   }
   print("Multiply numDens by distF...")
   local t1 = os.clock()
   pfldMult:advance(0.,{numDens,distF},{ndistF})
   local t2 = os.clock()
   io.write("ndistF computation took total of ", t2-t1, " s\n")

   local errF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }

   errF:combine(1.0, ndistFA, -1.0, ndistF)
   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)

   ndistF:write("ndistF.bp", 0.0)
   ndistFA:write("ndistFA.bp", 0.0)
   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)

   local calcIntF = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = phaseGrid,
      basis         = phaseBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecF = DataStruct.DynVector { numComponents = 1 }
   calcIntF:advance(0.0, {errF}, {dynVecF})
   local tmF, lvF = dynVecF:lastData()
   io.write("Average RMS in F error = ", math.sqrt(lvF[1]), "\n")

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1]), "\n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1]), "\n")
   print()
   return math.sqrt(lvF[1]), math.sqrt(lvUi[1]), math.sqrt(lvMom1[1])
end

------------------------------------------------------------------------------------
---                    Test in 1x2v
--- * Test weak division of a scalar 1x field by a scalar 1x field.
--- * Test weak multiplication of a scalar 1x field by a scalar 1x field.
--- * Test weak division of a 2D vector in 1x by a scalar 1x field.
--- * Test weak multiplication of a 2D vector in 1x by a scalar 1x field.
--- * Test weak multiplication of a 1x2v scalar field by a scalar 1x field.
------------------------------------------------------------------------------------
function test_binOp1x2v(nx, nvx, nvy, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local phaseGrid = Grid.RectCart {
      lower = {0.0, -1.0, -1.0},
      upper = {1.0, 1.0, 1.0},
      cells = {nx, nvx, nvy},
   }
   local confGrid = Grid.RectCart {
      lower = { phaseGrid:lower(1) },
      upper = { phaseGrid:upper(1) },
      cells = { phaseGrid:numCells(1) },
   }
   -- Basis functions.
   local phaseBasis = Basis.CartModalSerendipity { ndim = 3, polyOrder = p }
   local confBasis  = Basis.CartModalSerendipity { ndim = 1, polyOrder = p }
   io.write("nx=",nx," nvx=",nvx," nvy=",nvy," polyOrder=", p, "\n")

   -- Phase space distribution function.
   local distF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Analytic and calculated numDens*distF.
   local ndistF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   local ndistFA = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }
   local mom12D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local Ui2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }
   local UiA2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }

   -- Initialize distribution function. We will (weak) multiply this by numDens.
   local initDistF = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muV  = 0.0
                    local sigV = 0.8
                    local x, v = xn[1], xn[2]
                    return math.exp(-((v-muV)/(math.sqrt(2)*sigV))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initDistF:advance(0.,{},{distF})
   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
                    return math.exp(-x)
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x) 

                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   local initMom1i2D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*math.sin(4.0*2.0*math.pi*x), 
                           (math.exp(-x))*math.cos(4.0*2.0*math.pi*x)

                 end
   }
   initMom1i2D:advance(0.,{},{mom1A2D})
   -- Analytic numDens*distF.
   local initnDistFA = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muV  = 0.0
                    local sigV = 0.8
                    local x, v = xn[1], xn[2]
                    return math.exp(-x)*math.exp(-((v-muV)/(math.sqrt(2)*sigV))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initnDistFA:advance(0.,{},{ndistFA})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})
   local initUi2D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x = xn[1]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x), 
                           math.cos(4.0*2.0*math.pi*x)
                 end
   }
   initUi2D:advance(0.,{},{UiA2D})

   -- Multiply distribution function by number density.
   local pfldMult = Updater.CartFieldBinOp {
      onGrid     = phaseGrid,
      weakBasis  = phaseBasis,
      fieldBasis = confBasis,
      operation  = "Multiply",
   }
   print("Multiply numDens by distF...")
   local t1 = os.clock()
   pfldMult:advance(0.,{numDens,distF},{ndistF})
   local t2 = os.clock()
   io.write("ndistF computation took total of ", t2-t1, " s\n")

   -- Compute flow speed.
   local calcUi = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Divide",
   }
   print("Computing flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")
   print("Computing 2D flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A2D},{Ui2D})
   local t2 = os.clock()
   io.write("Ui2D computation took total of ", t2-t1, " s\n")

   -- Compute momentum.
   local calcMom1 = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")
   print("Computing 2D momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA2D},{mom12D})
   local t2 = os.clock()
   io.write("Mom12D computation took total of ", t2-t1, " s\n")

   local errF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost = {1, 1}
   }
   local errMom12D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost = {1, 1}
   }

   errF:combine(1.0, ndistFA, -1.0, ndistF)
   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)
   errU2D:combine(1.0, UiA2D, -1.0, Ui2D)
   errMom12D:combine(1.0, mom1A2D, -1.0, mom12D)

   ndistF:write("ndistF.bp", 0.0)
   ndistFA:write("ndistFA.bp", 0.0)
   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)

   local calcIntF = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = phaseGrid,
      basis         = phaseBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecF = DataStruct.DynVector { numComponents = 1 }
   calcIntF:advance(0.0, {errF}, {dynVecF})
   local tmF, lvF = dynVecF:lastData()
   io.write("Average RMS in F error = ", math.sqrt(lvF[1]), "\n")

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1])," \n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1])," \n")

   local calcInt2D = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 2,
      quantity      = "V2"
   }
   local dynVecUi2D = DataStruct.DynVector { numComponents = 2 }
   calcInt2D:advance(0.0, {errU2D}, {dynVecUi2D})
   local tmUi2D, lvUi2D = dynVecUi2D:lastData()
   io.write("Average RMS in Ui2D error = (", math.sqrt(lvUi2D[1]),",", math.sqrt(lvUi2D[2]),") \n")

   local dynVecMom12D = DataStruct.DynVector { numComponents = 2 }
   calcInt2D:advance(0.0, {errMom12D}, {dynVecMom12D})
   local tmMom12D, lvMom12D = dynVecMom12D:lastData()
   io.write("Average RMS in Mom12D error = (", math.sqrt(lvMom12D[1]),",", math.sqrt(lvMom12D[2]),") \n")
   print()
   return math.sqrt(lvF[1]), math.sqrt(lvUi[1]), math.sqrt(lvMom1[1]), 
          math.sqrt(lvUi2D[1]), math.sqrt(lvMom12D[1]), math.sqrt(lvUi2D[2]), math.sqrt(lvMom12D[2])
end

------------------------------------------------------------------------------------
---                    Test in 2x2v
--- * Test weak division of a scalar 2x field by a scalar 2x field.
--- * Test weak multiplication of a scalar 2x field by a scalar 2x field.
--- * Test weak division of a 2D vector in 2x by a scalar 2x field.
--- * Test weak multiplication of a 2D vector in 2x by a scalar 2x field.
--- * Test weak multiplication of a 2x2v scalar field by a scalar 2x field.
------------------------------------------------------------------------------------
function test_binOp2x2v(nx, ny, nvx, nvy, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local phaseGrid = Grid.RectCart {
      lower = {0.0, 1.0, -1.0, -1.0},
      upper = {1.0, 1.0,  1.0,  1.0},
      cells = {nx, ny, nvx, nvy},
   }
   local confGrid = Grid.RectCart {
      lower = { phaseGrid:lower(1), phaseGrid:lower(2) },
      upper = { phaseGrid:upper(1), phaseGrid:upper(2) },
      cells = { phaseGrid:numCells(1), phaseGrid:numCells(2) },
   }
   -- Basis functions.
   local phaseBasis = Basis.CartModalSerendipity { ndim = 4, polyOrder = p }
   local confBasis  = Basis.CartModalSerendipity { ndim = 2, polyOrder = p }
   io.write("nx=",nx," ny=",ny," nvx=",nvx," nvy=",nvy," polyOrder=", p, "\n")

   -- Phase space distribution function.
   local distF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Analytic and calculated numDens*distF.
   local ndistF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   local ndistFA = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }
   local mom12D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local Ui2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }
   local UiA2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost         = {1, 1},
   }

   -- Initialize distribution function. We will (weak) multiply this by numDens.
   local initDistF = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muVx  = 0.0
                    local sigVx = 0.8
                    local muVy  = 0.1
                    local sigVy = 0.6
                    local x, y, vx, vy = xn[1], xn[2], xn[3], xn[4]
                    return math.exp(-((vx-muVx)/(math.sqrt(2)*sigVx))^2-((vy-muVy)/(math.sqrt(2)*sigVy))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initDistF:advance(0.,{},{distF})
   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy = xn[1], xn[2], xn[3], xn[4]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
                    return math.exp(-x)*(2.0+math.tanh(y))
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy = xn[1], xn[2], xn[3], xn[4]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*(2.0+math.tanh(y))*math.sin(4.0*2.0*math.pi*x) 

                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   local initMom1i2D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy = xn[1], xn[2], xn[3], xn[4]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*(2.0+math.tanh(y))*math.sin(4.0*2.0*math.pi*x), 
                           (math.exp(-x))*(2.0+math.tanh(y))*math.cos(4.0*2.0*math.pi*x)

                 end
   }
   initMom1i2D:advance(0.,{},{mom1A2D})
   -- Analytic numDens*distF.
   local initnDistFA = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muVx  = 0.0
                    local sigVx = 0.8
                    local muVy  = 0.1
                    local sigVy = 0.6
                    local x, y, vx, vy = xn[1], xn[2], xn[3], xn[4]
                    return math.exp(-x)*(2.0+math.tanh(y))*
                           math.exp(-((vx-muVx)/(math.sqrt(2)*sigVx))^2-((vy-muVy)/(math.sqrt(2)*sigVy))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initnDistFA:advance(0.,{},{ndistFA})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy = xn[1], xn[2], xn[3], xn[4]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})
   local initUi2D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy = xn[1], xn[2], xn[3], xn[4]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x), 
                           math.cos(4.0*2.0*math.pi*x)
                 end
   }
   initUi2D:advance(0.,{},{UiA2D})

   -- Multiply distribution function by number density.
   local pfldMult = Updater.CartFieldBinOp {
      onGrid     = phaseGrid,
      weakBasis  = phaseBasis,
      fieldBasis = confBasis,
      operation  = "Multiply",
   }
   print("Multiply numDens by distF...")
   local t1 = os.clock()
   pfldMult:advance(0.,{numDens,distF},{ndistF})
   local t2 = os.clock()
   io.write("ndistF computation took total of ", t2-t1, " s\n")

   -- Compute flow speed.
   local calcUi = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Divide",
   }
   print("Computing flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")
   print("Computing 2D flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A2D},{Ui2D})
   local t2 = os.clock()
   io.write("Ui2D computation took total of ", t2-t1, " s\n")

   -- Compute momentum.
   local calcMom1 = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")
   print("Computing 2D momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA2D},{mom12D})
   local t2 = os.clock()
   io.write("Mom12D computation took total of ", t2-t1, " s\n")

   local errF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU2D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost = {1, 1}
   }
   local errMom12D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*2,
      ghost = {1, 1}
   }

   errF:combine(1.0, ndistFA, -1.0, ndistF)
   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)
   errU2D:combine(1.0, UiA2D, -1.0, Ui2D)
   errMom12D:combine(1.0, mom1A2D, -1.0, mom12D)

   ndistF:write("ndistF.bp", 0.0)
   ndistFA:write("ndistFA.bp", 0.0)
   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)

   local calcIntF = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = phaseGrid,
      basis         = phaseBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecF = DataStruct.DynVector { numComponents = 1 }
   calcIntF:advance(0.0, {errF}, {dynVecF})
   local tmF, lvF = dynVecF:lastData()
   io.write("Average RMS in F error = ", math.sqrt(lvF[1]), "\n")

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1])," \n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1])," \n")

   local calcInt2D = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 2,
      quantity      = "V2"
   }
   local dynVecUi2D = DataStruct.DynVector { numComponents = 2 }
   calcInt2D:advance(0.0, {errU2D}, {dynVecUi2D})
   local tmUi2D, lvUi2D = dynVecUi2D:lastData()
   io.write("Average RMS in Ui2D error = (", math.sqrt(lvUi2D[1]),",", math.sqrt(lvUi2D[2]),") \n")

   local dynVecMom12D = DataStruct.DynVector { numComponents = 2 }
   calcInt2D:advance(0.0, {errMom12D}, {dynVecMom12D})
   local tmMom12D, lvMom12D = dynVecMom12D:lastData()
   io.write("Average RMS in Mom12D error = (", math.sqrt(lvMom12D[1]),",", math.sqrt(lvMom12D[2]),") \n")
   print()
   return math.sqrt(lvF[1]), math.sqrt(lvUi[1]), math.sqrt(lvMom1[1]), 
          math.sqrt(lvUi2D[1]), math.sqrt(lvMom12D[1]), math.sqrt(lvUi2D[2]), math.sqrt(lvMom12D[2])
end

------------------------------------------------------------------------------------
---                    Test in 2x3v
--- * Test weak division of a scalar 2x field by a scalar 2x field.
--- * Test weak multiplication of a scalar 2x field by a scalar 2x field.
--- * Test weak division of a 3D vector in 2x by a scalar 2x field.
--- * Test weak multiplication of a 3D vector in 2x by a scalar 2x field.
--- * Test weak multiplication of a 2x3v scalar field by a scalar 2x field.
------------------------------------------------------------------------------------
function test_binOp2x3v(nx, ny, nvx, nvy, nvz, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local phaseGrid = Grid.RectCart {
      lower = {0.0, -1.0, -1.0, -1.0},
      upper = {1.0, 1.0, 1.0, 1.0, 1.0},
      cells = {nx, ny, nvx, nvy, nvz},
   }
   local confGrid = Grid.RectCart {
      lower = { phaseGrid:lower(1), phaseGrid:lower(2) },
      upper = { phaseGrid:upper(1), phaseGrid:upper(2) },
      cells = { phaseGrid:numCells(1), phaseGrid:numCells(2) },
   }
   -- Basis functions.
   local phaseBasis = Basis.CartModalSerendipity { ndim = 5, polyOrder = p }
   local confBasis  = Basis.CartModalSerendipity { ndim = 2, polyOrder = p }
   io.write("nx=",nx," ny=",ny," nvx=",nvx," nvy=",nvy," nvz=",nvz," polyOrder=", p, "\n")

   -- Phase space distribution function.
   local distF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Analytic and calculated numDens*distF.
   local ndistF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   local ndistFA = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }
   local mom13D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local Ui3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }
   local UiA3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }

   -- Initialize distribution function. We will (weak) multiply this by numDens.
   local initDistF = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muVx, sigVx  = 0.0, 0.8
                    local muVy, sigVy  = 0.1, 0.6
                    local muVz, sigVz  = -0.2, 0.3
                    local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]
                    return math.exp(-((vx-muVx)/(math.sqrt(2)*sigVx))^2-((vy-muVy)/(math.sqrt(2)*sigVy))^2
                                    -((vz-muVz)/(math.sqrt(2)*sigVz))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initDistF:advance(0.,{},{distF})
   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
                    return math.exp(-x)*(2.0+math.tanh(y))
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*(2.0+math.tanh(y))*math.sin(4.0*2.0*math.pi*x) 

                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   local initMom1i3D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*(2.0+math.tanh(y))*math.sin(4.0*2.0*math.pi*x), 
                           (math.exp(-x))*(2.0+math.tanh(y))*math.cos(4.0*2.0*math.pi*y),
                           (math.exp(-x))*(2.0+math.tanh(y))*0.760

                 end
   }
   initMom1i3D:advance(0.,{},{mom1A3D})
   -- Analytic numDens*distF.
   local initnDistFA = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muVx, sigVx  = 0.0, 0.8
                    local muVy, sigVy  = 0.1, 0.6
                    local muVz, sigVz  = -0.2, 0.3
                    local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]
                    return math.exp(-x)*(2.0+math.tanh(y))*
                           math.exp(-((vx-muVx)/(math.sqrt(2)*sigVx))^2-((vy-muVy)/(math.sqrt(2)*sigVy))^2
                                    -((vz-muVz)/(math.sqrt(2)*sigVz))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initnDistFA:advance(0.,{},{ndistFA})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})
   local initUi3D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, vx, vy, vz = xn[1], xn[2], xn[3], xn[4], xn[5]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x), 
                           math.cos(4.0*2.0*math.pi*y),
                           0.760
                 end
   }
   initUi3D:advance(0.,{},{UiA3D})

   -- Multiply distribution function by number density.
   local pfldMult = Updater.CartFieldBinOp {
      onGrid     = phaseGrid,
      weakBasis  = phaseBasis,
      fieldBasis = confBasis,
      operation  = "Multiply",
   }
   print("Multiply numDens by distF...")
   local t1 = os.clock()
   pfldMult:advance(0.,{numDens,distF},{ndistF})
   local t2 = os.clock()
   io.write("ndistF computation took total of ", t2-t1, " s\n")

   -- Compute flow speed.
   local calcUi = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Divide",
   }
   print("Computing flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")
   print("Computing 3D flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A3D},{Ui3D})
   local t2 = os.clock()
   io.write("Ui3D computation took total of ", t2-t1, " s\n")

   -- Compute momentum.
   local calcMom1 = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")
   print("Computing 3D momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA3D},{mom13D})
   local t2 = os.clock()
   io.write("Mom13D computation took total of ", t2-t1, " s\n")

   local errF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost = {1, 1}
   }
   local errMom13D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost = {1, 1}
   }

   errF:combine(1.0, ndistFA, -1.0, ndistF)
   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)
   errU3D:combine(1.0, UiA3D, -1.0, Ui3D)
   errMom13D:combine(1.0, mom1A3D, -1.0, mom13D)

   ndistF:write("ndistF.bp", 0.0)
   ndistFA:write("ndistFA.bp", 0.0)
   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)

   local calcIntF = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = phaseGrid,
      basis         = phaseBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecF = DataStruct.DynVector { numComponents = 1 }
   calcIntF:advance(0.0, {errF}, {dynVecF})
   local tmF, lvF = dynVecF:lastData()
   io.write("Average RMS in F error = ", math.sqrt(lvF[1]), "\n")

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1])," \n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1])," \n")

   local calcInt3D = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 3,
      quantity      = "V2"
   }
   local dynVecUi3D = DataStruct.DynVector { numComponents = 3 }
   calcInt3D:advance(0.0, {errU3D}, {dynVecUi3D})
   local tmUi3D, lvUi3D = dynVecUi3D:lastData()
   io.write("Average RMS in Ui3D error = (", math.sqrt(lvUi3D[1]),",", math.sqrt(lvUi3D[2]),",", math.sqrt(lvUi3D[3]),") \n")

   local dynVecMom13D = DataStruct.DynVector { numComponents = 3 }
   calcInt3D:advance(0.0, {errMom13D}, {dynVecMom13D})
   local tmMom13D, lvMom13D = dynVecMom13D:lastData()
   io.write("Average RMS in Mom13D error = (", math.sqrt(lvMom13D[1]),",", math.sqrt(lvMom13D[2]),",", math.sqrt(lvMom13D[3]),") \n")
   print()
   return math.sqrt(lvF[1]), math.sqrt(lvUi[1]), math.sqrt(lvMom1[1]), 
          math.sqrt(lvUi3D[1]), math.sqrt(lvMom13D[1]), math.sqrt(lvUi3D[2]), math.sqrt(lvMom13D[2]), 
          math.sqrt(lvUi3D[3]), math.sqrt(lvMom13D[3])
end

------------------------------------------------------------------------------------
---                    Test in 3x2v
--- * Test weak division of a scalar 3x field by a scalar 3x field.
--- * Test weak multiplication of a scalar 3x field by a scalar 3x field.
--- * Test weak division of a 2D vector in 3x by a scalar 3x field.
--- * Test weak multiplication of a 2D vector in 3x by a scalar 3x field.
--- * Test weak multiplication of a 3x2v scalar field by a scalar 3x field.
------------------------------------------------------------------------------------
function test_binOp3x2v(nx, ny, nz, nvx, nvy, p, writeMatrix)
   writeMatrix = writeMatrix or false
   -- Phase-space and config-space grids.
   local phaseGrid = Grid.RectCart {
      lower = {0.0, 0.0, 0.0, -1.0, -1.0},
      upper = {1.0, 1.0, 1.0,  1.0,  1.0},
      cells = {nx, ny, nz, nvx, nvy},
   }
   local confGrid = Grid.RectCart {
      lower = { phaseGrid:lower(1), phaseGrid:lower(2), phaseGrid:lower(3) },
      upper = { phaseGrid:upper(1), phaseGrid:upper(2), phaseGrid:upper(3)  },
      cells = { phaseGrid:numCells(1), phaseGrid:numCells(2), phaseGrid:numCells(3)  },
   }
   -- Basis functions.
   local phaseBasis = Basis.CartModalSerendipity { ndim = 5, polyOrder = p }
   local confBasis  = Basis.CartModalSerendipity { ndim = 3, polyOrder = p }
   io.write("nx=",nx," ny=",ny," nz=",nz," nvx=",nvx," nvy=",nvy," polyOrder=", p, "\n")

   -- Phase space distribution function.
   local distF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Analytic and calculated numDens*distF.
   local ndistF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   local ndistFA = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost         = {1, 1},
   }
   -- Zeroth and first moments.
   local numDens = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local mom1A3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }
   local mom13D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }
   -- Calculated and analytic flow speed.
   local Ui = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local UiA = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost         = {1, 1},
   }
   local Ui3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }
   local UiA3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost         = {1, 1},
   }

   -- Initialize distribution function. We will (weak) multiply this by numDens.
   local initDistF = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muVx  = 0.0
                    local sigVx = 0.8
                    local muVy  = 0.1
                    local sigVy = 0.6
                    local x, y, z, vx, vy = xn[1], xn[2], xn[3], xn[4], xn[5]
                    return math.exp(-((vx-muVx)/(math.sqrt(2)*sigVx))^2-((vy-muVy)/(math.sqrt(2)*sigVy))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initDistF:advance(0.,{},{distF})
   -- Initialize number density and first moment.
   local initDens = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z, vx, vy = xn[1], xn[2], xn[3], xn[4], xn[5]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
                    return math.exp(-x)*(2.0+math.tanh(y))*(1.1-z)
                 end
   }
   initDens:advance(0.,{},{numDens})
   local initMom1i = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z, vx, vy = xn[1], xn[2], xn[3], xn[4], xn[5]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*(2.0+math.tanh(y))*(1.1-z)*math.sin(4.0*2.0*math.pi*x) 

                 end
   }
   initMom1i:advance(0.,{},{mom1A})
   local initMom1i3D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z, vx, vy = xn[1], xn[2], xn[3], xn[4], xn[5]
--                      return (math.exp(-((x-mu)/(math.sqrt(2)*sig))^2))*math.tanh(x-0.5)
--                      return (0.90-x)*math.tanh(x-0.5)
--                    return (0.90-x)*math.sin(4.0*2.0*math.pi*x)
--                    return (math.exp(-x)-0.5)*math.sin(4.0*2.0*math.pi*x)
                    return (math.exp(-x))*(2.0+math.tanh(y))*(1.1-z)*math.sin(4.0*2.0*math.pi*x), 
                           (math.exp(-x))*(2.0+math.tanh(y))*(1.1-z)*math.cos(4.0*2.0*math.pi*y),
                           (math.exp(-x))*(2.0+math.tanh(y))*(1.1-z)*math.tanh(z)

                 end
   }
   initMom1i3D:advance(0.,{},{mom1A3D})
   -- Analytic numDens*distF.
   local initnDistFA = Updater.ProjectOnBasis {
      onGrid   = phaseGrid,
      basis    = phaseBasis,
      evaluate = function (t,xn)
                    local muVx  = 0.0
                    local sigVx = 0.8
                    local muVy  = 0.1
                    local sigVy = 0.6
                    local x, y, z, vx, vy = xn[1], xn[2], xn[3], xn[4], xn[5]
                    return math.exp(-x)*(2.0+math.tanh(y))*(1.1-z)*
                           math.exp(-((vx-muVx)/(math.sqrt(2)*sigVx))^2-((vy-muVy)/(math.sqrt(2)*sigVy))^2)
--                    return 0.90-x
--                    return math.exp(-x)-0.5
--                    return math.exp(-x)
                 end
   }
   initnDistFA:advance(0.,{},{ndistFA})
   -- Analytic flow speed.
   local initUi = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z, vx, vy = xn[1], xn[2], xn[3], xn[4], xn[5]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x)
                 end
   }
   initUi:advance(0.,{},{UiA})
   local initUi3D = Updater.ProjectOnBasis {
      onGrid   = confGrid,
      basis    = confBasis,
      evaluate = function (t,xn)
                    local mu  = 0.5
                    local sig = 0.04
                    local x, y, z, vx, vy = xn[1], xn[2], xn[3], xn[4], xn[5]
--                    return math.exp(-((x-mu)/(math.sqrt(2)*sig))^2)
--                    return math.tanh(x-0.5)
                    return math.sin(4.0*2.0*math.pi*x), 
                           math.cos(4.0*2.0*math.pi*y),
                           math.tanh(z)
                 end
   }
   initUi3D:advance(0.,{},{UiA3D})

   -- Multiply distribution function by number density.
   local pfldMult = Updater.CartFieldBinOp {
      onGrid     = phaseGrid,
      weakBasis  = phaseBasis,
      fieldBasis = confBasis,
      operation  = "Multiply",
   }
   print("Multiply numDens by distF...")
   local t1 = os.clock()
   pfldMult:advance(0.,{numDens,distF},{ndistF})
   local t2 = os.clock()
   io.write("ndistF computation took total of ", t2-t1, " s\n")

   -- Compute flow speed.
   local calcUi = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Divide",
   }
   print("Computing flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A},{Ui})
   local t2 = os.clock()
   io.write("Ui computation took total of ", t2-t1, " s\n")
   print("Computing 3D flow speed...")
   local t1 = os.clock()
   calcUi:advance(0.,{numDens,mom1A3D},{Ui3D})
   local t2 = os.clock()
   io.write("Ui3D computation took total of ", t2-t1, " s\n")

   -- Compute momentum.
   local calcMom1 = Updater.CartFieldBinOp {
      onGrid     = confGrid,
      weakBasis  = confBasis,
      operation  = "Multiply",
   }
   print("Computing momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA},{mom1})
   local t2 = os.clock()
   io.write("Mom1 computation took total of ", t2-t1, " s\n")
   print("Computing 3D momentum...")
   local t1 = os.clock()
   calcMom1:advance(0.,{numDens,UiA3D},{mom13D})
   local t2 = os.clock()
   io.write("Mom13D computation took total of ", t2-t1, " s\n")

   local errF = DataStruct.Field {
      onGrid        = phaseGrid,
      numComponents = phaseBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errMom1 = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis(),
      ghost = {1, 1}
   }
   local errU3D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost = {1, 1}
   }
   local errMom13D = DataStruct.Field {
      onGrid        = confGrid,
      numComponents = confBasis:numBasis()*3,
      ghost = {1, 1}
   }

   errF:combine(1.0, ndistFA, -1.0, ndistF)
   errU:combine(1.0, UiA, -1.0, Ui)
   errMom1:combine(1.0, mom1A, -1.0, mom1)
   errU3D:combine(1.0, UiA3D, -1.0, Ui3D)
   errMom13D:combine(1.0, mom1A3D, -1.0, mom13D)

   ndistF:write("ndistF.bp", 0.0)
   ndistFA:write("ndistFA.bp", 0.0)
   numDens:write("numDens.bp", 0.0)
   mom1A:write("mom1A.bp", 0.0)
   mom1:write("mom1.bp", 0.0)
   Ui:write("Ui.bp", 0.0)
   UiA:write("UiA.bp", 0.0)

   local calcIntF = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = phaseGrid,
      basis         = phaseBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecF = DataStruct.DynVector { numComponents = 1 }
   calcIntF:advance(0.0, {errF}, {dynVecF})
   local tmF, lvF = dynVecF:lastData()
   io.write("Average RMS in F error = ", math.sqrt(lvF[1]), "\n")

   local calcInt = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 1,
      quantity      = "V2"
   }
   local dynVecUi = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errU}, {dynVecUi})
   local tmUi, lvUi = dynVecUi:lastData()
   io.write("Average RMS in Ui error = ", math.sqrt(lvUi[1])," \n")

   local dynVecMom1 = DataStruct.DynVector { numComponents = 1 }
   calcInt:advance(0.0, {errMom1}, {dynVecMom1})
   local tmMom1, lvMom1 = dynVecMom1:lastData()
   io.write("Average RMS in Mom1 error = ", math.sqrt(lvMom1[1])," \n")

   local calcInt3D = Updater.CartFieldIntegratedQuantCalc {
      onGrid        = confGrid,
      basis         = confBasis,
      numComponents = 3,
      quantity      = "V2"
   }
   local dynVecUi3D = DataStruct.DynVector { numComponents = 3 }
   calcInt3D:advance(0.0, {errU3D}, {dynVecUi3D})
   local tmUi3D, lvUi3D = dynVecUi3D:lastData()
   io.write("Average RMS in Ui3D error = (", math.sqrt(lvUi3D[1]),",", math.sqrt(lvUi3D[2]),",", math.sqrt(lvUi3D[3]),") \n")

   local dynVecMom13D = DataStruct.DynVector { numComponents = 3 }
   calcInt3D:advance(0.0, {errMom13D}, {dynVecMom13D})
   local tmMom13D, lvMom13D = dynVecMom13D:lastData()
   io.write("Average RMS in Mom13D error = (", math.sqrt(lvMom13D[1]),",", math.sqrt(lvMom13D[2]),",", math.sqrt(lvMom13D[3]),") \n")
   print()
   return math.sqrt(lvF[1]), math.sqrt(lvUi[1]), math.sqrt(lvMom1[1]), 
          math.sqrt(lvUi3D[1]), math.sqrt(lvMom13D[1]), math.sqrt(lvUi3D[2]), math.sqrt(lvMom13D[2]), 
          math.sqrt(lvUi3D[3]), math.sqrt(lvMom13D[3])
end

-------------------------------------------------------
-- Call tests in 1x for various resolutions
-------------------------------------------------------
function binOp1x_conv(p)
  print(" ")
  print("--- Testing convergence of BinOpSer1x updater with p=",p," ---")
  errUi1, errMom11, errMom1Sq1 = test_binOp1x(32, p)
  errUi2, errMom12, errMom1Sq2 = test_binOp1x(64, p)
  errUi3, errMom13, errMom1Sq3 = test_binOp1x(128, p)
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("Multiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                           math.log10(errMom12/errMom13)/math.log10(2.0))
  print("DotProduct order:", math.log10(errMom1Sq1/errMom1Sq2)/math.log10(2.0), 
                             math.log10(errMom1Sq2/errMom1Sq3)/math.log10(2.0))
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-------------------------------------------------------
-- Call tests in 2x for various resolutions
-------------------------------------------------------
function binOp2x_conv(p)
  print(" ")
  print("--- Testing convergence of BinOpSer2x updater with p=",p," ---")
  errUi1, errMom11, errUi2Dx1, errMom12Dx1, 
    errUi2Dy1, errMom12Dy1, errUsq1, errKe1 = test_binOp2x(32, 32, p)
  errUi2, errMom12, errUi2Dx2, errMom12Dx2,
    errUi2Dy2, errMom12Dy2, errUsq2, errKe2 = test_binOp2x(64, 64, p)
  errUi3, errMom13, errUi2Dx3, errMom12Dx3,
    errUi2Dy3, errMom12Dy3, errUsq3, errKe3 = test_binOp2x(128, 128, p)
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("Multiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                           math.log10(errMom12/errMom13)/math.log10(2.0))
  print("Same field DotProduct order:", math.log10(errUsq1/errUsq2)/math.log10(2.0), 
                                        math.log10(errUsq2/errUsq3)/math.log10(2.0))
  print("Different field DotProduct order:", math.log10(errKe1/errKe2)/math.log10(2.0), 
                                             math.log10(errKe2/errKe3)/math.log10(2.0))
  print("2D Division order: (", math.log10(errUi2Dx1/errUi2Dx2)/math.log10(2.0),",", 
    math.log10(errUi2Dy1/errUi2Dy2)/math.log10(2.0),")  (", 
    math.log10(errUi2Dx2/errUi2Dx3)/math.log10(2.0),",", math.log10(errUi2Dy2/errUi2Dy3)/math.log10(2.0))
  print("2D Multiply order: (", math.log10(errMom12Dx1/errMom12Dx2)/math.log10(2.0),",", 
    math.log10(errMom12Dy1/errMom12Dy2)/math.log10(2.0),")  (", 
    math.log10(errMom12Dx2/errMom12Dx3)/math.log10(2.0),",", math.log10(errMom12Dy2/errMom12Dy3)/math.log10(2.0))
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-------------------------------------------------------
-- Call tests in 3x for various resolutions
-------------------------------------------------------
function binOp3x_conv(p)
  print(" ")
  print("--- Testing convergence of BinOpSer3x updater with p=",p," ---")
  errUi1, errMom11, errUi3Dx1, errMom13Dx1, errUi3Dy1, errMom13Dy1, 
    errUi3Dz1, errMom13Dz1, errUsq1, errKe1 = test_binOp3x(32, 32, 32, p)
  errUi2, errMom12, errUi3Dx2, errMom13Dx2, errUi3Dy2, errMom13Dy2, 
    errUi3Dz2, errMom13Dz2, errUsq2, errKe2 = test_binOp3x(64, 64, 64, p)
  errUi3, errMom13, errUi3Dx3, errMom13Dx3, errUi3Dy3, errMom13Dy3, 
    errUi3Dz3, errMom13Dz3, errUsq3, errKe3 = test_binOp3x(128, 128, 128, p)
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("Multiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                           math.log10(errMom12/errMom13)/math.log10(2.0))
  print("Same field DotProduct order:", math.log10(errUsq1/errUsq2)/math.log10(2.0), 
                                        math.log10(errUsq2/errUsq3)/math.log10(2.0))
  print("Different field DotProduct order:", math.log10(errKe1/errKe2)/math.log10(2.0), 
                                             math.log10(errKe2/errKe3)/math.log10(2.0))
  print("3D Division order: (", math.log10(errUi3Dx1/errUi3Dx2)/math.log10(2.0),",", 
    math.log10(errUi3Dy1/errUi3Dy2)/math.log10(2.0),",",math.log10(errUi3Dz1/errUi3Dz2)/math.log10(2.0),")  (", 
    math.log10(errUi3Dx2/errUi3Dx3)/math.log10(2.0),",", math.log10(errUi3Dy2/errUi3Dy3)/math.log10(2.0),",",math.log10(errUi3Dz2/errUi3Dz3)/math.log10(2.0),")")
  print("3D Multiply order: (", math.log10(errMom13Dx1/errMom13Dx2)/math.log10(2.0),",", 
    math.log10(errMom13Dy1/errMom13Dy2)/math.log10(2.0),",",math.log10(errMom13Dz1/errMom13Dz2)/math.log10(2.0),")  (", 
    math.log10(errMom13Dx2/errMom13Dx3)/math.log10(2.0),",", math.log10(errMom13Dy2/errMom13Dy3)/math.log10(2.0),",",math.log10(errMom13Dz2/errMom13Dz3)/math.log10(2.0),")")
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-------------------------------------------------------
-- Call tests in 1x1v for various resolutions
-------------------------------------------------------
function binOp1x1v_conv(p)
  print(" ")
  print("--- Testing convergence of BinOpSer1x1v updater with p=",p," ---")
  errF1, errUi1, errMom11 = test_binOp1x1v(32, 8, p)
  errF2, errUi2, errMom12 = test_binOp1x1v(64, 8, p)
  errF3, errUi3, errMom13 = test_binOp1x1v(128, 8, p)
  print("phaseMultiply order:", math.log10(errF1/errF2)/math.log10(2.0), 
                                math.log10(errF2/errF3)/math.log10(2.0))
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("confMultiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                               math.log10(errMom12/errMom13)/math.log10(2.0))
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-------------------------------------------------------
-- Call tests in 1x2v for various resolutions
-------------------------------------------------------
function binOp1x2v_conv(p)
  print("--- Testing convergence of BinOpSer1x2v updater with p=",p," ---")
  errF1, errUi1, errMom11, errUi1x, errMom11x, errUi1y, errMom11y = test_binOp1x2v(32, 32, 32, p)
  errF2, errUi2, errMom12, errUi2x, errMom12x, errUi2y, errMom12y = test_binOp1x2v(64, 64, 64, p)
  errF3, errUi3, errMom13, errUi3x, errMom13x, errUi3y, errMom13y = test_binOp1x2v(128, 128, 128, p)
  print("phaseMultiply order:", math.log10(errF1/errF2)/math.log10(2.0), 
                                math.log10(errF2/errF3)/math.log10(2.0))
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("Multiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                           math.log10(errMom12/errMom13)/math.log10(2.0))
  print("2D Division order: (", math.log10(errUi1x/errUi2x)/math.log10(2.0),",", 
    math.log10(errUi1y/errUi2y)/math.log10(2.0),")  (", 
    math.log10(errUi2x/errUi3x)/math.log10(2.0),",", math.log10(errUi2x/errUi3x)/math.log10(2.0),")")
  print("2D Multiply order: (", math.log10(errMom11x/errMom12x)/math.log10(2.0),",", 
    math.log10(errMom11y/errMom12y)/math.log10(2.0),")  (", 
    math.log10(errMom12x/errMom13x)/math.log10(2.0),",", math.log10(errMom12x/errMom13x)/math.log10(2.0),")")
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-------------------------------------------------------
-- Call tests in 2x2v for various resolutions
-------------------------------------------------------
function binOp2x2v_conv(p)
  print("--- Testing convergence of BinOpSer2x2v updater with p=",p," ---")
  errF1, errUi1, errMom11, errUi1x, errMom11x, errUi1y, errMom11y = test_binOp2x2v(8, 8, 8, 8, p)
  errF2, errUi2, errMom12, errUi2x, errMom12x, errUi2y, errMom12y = test_binOp2x2v(32, 32, 32, 32, p)
  errF3, errUi3, errMom13, errUi3x, errMom13x, errUi3y, errMom13y = test_binOp2x2v(64, 64, 64, 64, p)
  print("phaseMultiply order:", math.log10(errF1/errF2)/math.log10(2.0), 
                                math.log10(errF2/errF3)/math.log10(2.0))
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("Multiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                           math.log10(errMom12/errMom13)/math.log10(2.0))
  print("2D Division order: (", math.log10(errUi1x/errUi2x)/math.log10(2.0),",", 
    math.log10(errUi1y/errUi2y)/math.log10(2.0),")  (", 
    math.log10(errUi2x/errUi3x)/math.log10(2.0),",", math.log10(errUi2x/errUi3x)/math.log10(2.0),")")
  print("2D Multiply order: (", math.log10(errMom11x/errMom12x)/math.log10(2.0),",", 
    math.log10(errMom11y/errMom12y)/math.log10(2.0),")  (", 
    math.log10(errMom12x/errMom13x)/math.log10(2.0),",", math.log10(errMom12x/errMom13x)/math.log10(2.0),")")
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-------------------------------------------------------
-- Call tests in 2x3v for various resolutions
-------------------------------------------------------
function binOp2x3v_conv(p)
  print("--- Testing convergence of BinOpSer2x3v updater with p=",p," ---")
  errF1, errUi1, errMom11, errUi1x, errMom11x, 
    errUi1y, errMom11y, errUi1z, errMom11z = test_binOp2x3v(8, 8, 8, 8, 8, p)
  errF2, errUi2, errMom12, errUi2x, errMom12x, 
    errUi2y, errMom12y, errUi2z, errMom12z = test_binOp2x3v(16, 16, 16, 16, 16, p)
  errF3, errUi3, errMom13, errUi3x, errMom13x, 
    errUi3y, errMom13y, errUi3z, errMom13z = test_binOp2x3v(32, 32, 32, 32, 32, p)
  print("phaseMultiply order:", math.log10(errF1/errF2)/math.log10(2.0), 
                                math.log10(errF2/errF3)/math.log10(2.0))
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("Multiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                           math.log10(errMom12/errMom13)/math.log10(2.0))
  print("3D Division order: (", math.log10(errUi1x/errUi2x)/math.log10(2.0),",", 
    math.log10(errUi1y/errUi2y)/math.log10(2.0),",",math.log10(errUi1z/errUi2z)/math.log10(2.0),")  (", 
    math.log10(errUi2x/errUi3x)/math.log10(2.0),",", math.log10(errUi2x/errUi3x)/math.log10(2.0),",",
    math.log10(errUi2z/errUi3z)/math.log10(2.0),")")
  print("3D Multiply order: (", math.log10(errMom11x/errMom12x)/math.log10(2.0),",", 
    math.log10(errMom11y/errMom12y)/math.log10(2.0),",",math.log10(errMom11z/errMom12z)/math.log10(2.0),")  (", 
    math.log10(errMom12x/errMom13x)/math.log10(2.0),",", math.log10(errMom12x/errMom13x)/math.log10(2.0),",",
    math.log10(errMom12z/errMom13z)/math.log10(2.0),")")
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-------------------------------------------------------
-- Call tests in 3x2v for various resolutions
-------------------------------------------------------
function binOp3x2v_conv(p)
  print("--- Testing convergence of BinOpSer3x2v updater with p=",p," ---")
  errF1, errUi1, errMom11, errUi1x, errMom11x, 
    errUi1y, errMom11y, errUi1z, errMom11z = test_binOp3x2v(8, 8, 8, 8, 8, p)
  errF2, errUi2, errMom12, errUi2x, errMom12x, 
    errUi2y, errMom12y, errUi2z, errMom12z = test_binOp3x2v(16, 16, 16, 16, 16, p)
  errF3, errUi3, errMom13, errUi3x, errMom13x, 
    errUi3y, errMom13y, errUi3z, errMom13z = test_binOp3x2v(32, 32, 32, 32, 32, p)
  print("phaseMultiply order:", math.log10(errF1/errF2)/math.log10(2.0), 
                                math.log10(errF2/errF3)/math.log10(2.0))
  print("Division order:", math.log10(errUi1/errUi2)/math.log10(2.0), 
                           math.log10(errUi2/errUi3)/math.log10(2.0))
  print("Multiply order:", math.log10(errMom11/errMom12)/math.log10(2.0), 
                           math.log10(errMom12/errMom13)/math.log10(2.0))
  print("3D Division order: (", math.log10(errUi1x/errUi2x)/math.log10(2.0),",", 
    math.log10(errUi1y/errUi2y)/math.log10(2.0),",",math.log10(errUi1z/errUi2z)/math.log10(2.0),")  (", 
    math.log10(errUi2x/errUi3x)/math.log10(2.0),",", math.log10(errUi2x/errUi3x)/math.log10(2.0),",",
    math.log10(errUi2z/errUi3z)/math.log10(2.0),")")
  print("3D Multiply order: (", math.log10(errMom11x/errMom12x)/math.log10(2.0),",", 
    math.log10(errMom11y/errMom12y)/math.log10(2.0),",",math.log10(errMom11z/errMom12z)/math.log10(2.0),")  (", 
    math.log10(errMom12x/errMom13x)/math.log10(2.0),",", math.log10(errMom12x/errMom13x)/math.log10(2.0),",",
    math.log10(errMom12z/errMom13z)/math.log10(2.0),")")
--  assert_close(1.0, err1/err2/4.0, .01)
--  assert_close(1.0, err2/err3/4.0, .01)
  print()
end

-- run tests
local t1 = os.clock()
-- binOp1x_conv(1)
-- binOp1x_conv(2)
-- binOp2x_conv(1)
binOp2x_conv(2)
-- binOp3x_conv(1)  -- This one takes a little time.
-- binOp3x_conv(2)  -- This one takes more than a little time.
-- binOp1x1v_conv(1)
-- binOp1x1v_conv(2)
-- binOp1x2v_conv(1)
-- binOp1x2v_conv(2)
-- binOp2x2v_conv(1)
-- binOp2x2v_conv(2)
-- binOp2x3v_conv(1)
-- binOp2x3v_conv(2)
-- binOp3x2v_conv(1)
-- binOp3x2v_conv(2)
local t2 = os.clock()

print()
-- if stats.fail > 0 then
--    print(string.format("\nPASSED %d tests", stats.pass))
--    print(string.format("**** FAILED %d tests", stats.fail))
-- else
--    print(string.format("PASSED ALL %d tests!", stats.pass))
-- end
print(string.format("Tests finished! Check RMS error and order of convergence."))
io.write("Total test time: ", t2-t1, " s\n")
