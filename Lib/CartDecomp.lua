-- Gkyl ------------------------------------------------------------------------
--
-- Decomposition algorithms for rectangular grids.
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

-- system libraries
local ffi = require "ffi"
local xsys = require "xsys"
local new, copy, fill, sizeof, typeof, metatype = xsys.from(ffi,
     "new, copy, fill, sizeof, typeof, metatype")

-- Gkyl libraries
local Range = require "Lib.Range"
local Lin = require "Lib.Linalg"

-- CartProdDecomp --------------------------------------------------------------
--
-- Decomposition of grid into smaller boxes, specified by number of
-- cuts in each direction
--------------------------------------------------------------------------------

-- create constructor to store vector of Range objects
local RangeVec = Lin.new_vec_ct(ffi.typeof("Range_t"))

local CartProdDecomp = {}
-- constructor to make new cart-prod decomp
function CartProdDecomp:new(tbl)
   local self = setmetatable({}, CartProdDecomp)
   
   local ones = {}
   for d = 1, #tbl.cuts do ones[d] = 1 end
   self._cutsRange = Range.Range(ones, tbl.cuts)
   self._domains = RangeVec(self._cutsRange:volume())

   return self
end

-- make object callable, and redirect call to the :new method
setmetatable(CartProdDecomp, { __call = function (self, o) return self.new(self, o) end })

-- set callable methods
CartProdDecomp.__index = {
   ndim = function (self)
      return self._cutsRange:ndim()
   end,
   cuts = function (self, dir)
      return self._cutsRange:upper(dir)
   end,
   decompose = function (self, range) -- decompose range
      local shapes = {} -- to store shapes in each direction
      -- compute shape in each direction
      for dir = 1, range:ndim() do
	 shapes[dir] = Lin.IntVec(self:cuts(dir))
	 local baseShape = math.floor(range:shape(dir)/self:cuts(dir))
	 local remCells = range:shape(dir) % self:cuts(dir)	 
	 for c = 1, self:cuts(dir) do
	    shapes[dir][c] = baseShape + (remCells>0 and 1 or 0) -- add extra cell, if any
	    remCells = remCells-1
	 end
      end

      return true
   end,
   lower = function (self, dir, c) -- c is cut number
      return 0
   end,
   upper = function (self, dir, c) -- c is cut number
      return 1
   end
}

return {
   CartProd = CartProdDecomp,
}
