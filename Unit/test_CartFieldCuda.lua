-- Gkyl ------------------------------------------------------------------------
--
-- Test for fields on cartesian grids
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

local ffi = require "ffi"
local Unit = require "Unit"
local Grid = require "Grid"
local DataStruct = require "DataStruct"

local assert_equal = Unit.assert_equal
local stats = Unit.stats

function test_1()
   local grid = Grid.RectCart {
      lower = {0.0},
      upper = {1.0},
      cells = {1000},
   }
   local field = DataStruct.Field {
      onGrid = grid,
      numComponents = 3,
      ghost = {1, 1},
      createDeviceCopy = true,
   }
   local field2 = DataStruct.Field {
      onGrid = grid,
      numComponents = 3,
      ghost = {1, 1},
      createDeviceCopy = true,
   }

   local localRange = field:localRange()
   local indexer = field:indexer()
   for i = localRange:lower(1), localRange:upper(1) do
      local fitr = field:get(indexer(i))
      fitr[1] = i+1
      fitr[2] = i+2
      fitr[3] = i+3
   end

   -- copy stuff to device
   local err = field:copyHostToDevice()
   local err2 = field2:copyHostToDevice()
   assert_equal(0, err, "Checking if copy to device worked")
   assert_equal(0, err2, "Checking if copy to device worked")

   field:deviceScale(-0.5)
   field:deviceAbs()
   field2:deviceClear(1.0)
   field:deviceAccumulate(2.0, field2, 0.5, field2)
   field:copyDeviceToHost()

   if GKYL_HAVE_CUDA then
      for i = localRange:lower(1), localRange:upper(1) do
	 local fitr = field:get(indexer(i))
	 assert_equal(0.5*(i+1)+2.5, fitr[1], "Checking deviceScale")
	 assert_equal(0.5*(i+2)+2.5, fitr[2], "Checking deviceScale")
	 assert_equal(0.5*(i+3)+2.5, fitr[3], "Checking deviceScale")
      end
   end
end

test_1()

if stats.fail > 0 then
   print(string.format("\nPASSED %d tests", stats.pass))
   print(string.format("**** FAILED %d tests", stats.fail))
else
   print(string.format("PASSED ALL %d tests!", stats.pass))
end
