-- Gkyl ------------------------------------------------------------------------
--
-- Dispatch into Vlasov C++ kernel functions based on CDIM, VDIM,
-- basis functions and polyOrder.
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

local ffi = require "ffi"
local _ = require "Eq.vlasovData._VlasovCdef"

-- "do nothing" function
local function nullFunc(...) end

-- map of basis function name -> function encoding
local basisNmMap = { ["serendipity"] = "Ser", ["maximal-order"] = "Max", ["tensor"] = "Tensor" }

local _M = {}

-- select function to compute volume streaming terms
function _M.selectVolStream(basisNm, CDIM, VDIM, polyOrder)
   local funcNm = string.format("VlasovVolStream%dx%dv%sP%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
   return ffi.C[funcNm]
end

-- select functions to compute surface streaming terms (output is a table of functions)
function _M.selectSurfStream(basisNm, CDIM, VDIM, polyOrder)
   if CDIM == 1 then
      local funcNmX = string.format("VlasovSurfStream%dx%dv%s_X_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      return { ffi.C[funcNmX] }
   elseif CDIM == 2 then
      local funcNmX = string.format("VlasovSurfStream%dx%dv%s_X_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      local funcNmY = string.format("VlasovSurfStream%dx%dv%s_Y_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      return { ffi.C[funcNmX], ffi.C[funcNmY] }
   elseif CDIM == 3 then
      local funcNmX = string.format("VlasovSurfStream%dx%dv%s_X_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      local funcNmY = string.format("VlasovSurfStream%dx%dv%s_Y_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      local funcNmZ = string.format("VlasovSurfStream%dx%dv%s_Z_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      return { ffi.C[funcNmX], ffi.C[funcNmY], ffi.C[funcNmZ] }
   end
end

-- select function to compute volume EM field acceleration terms
function _M.selectVolElcMag(basisNm, CDIM, VDIM, polyOrder)
   local funcNm = string.format("VlasovVol%dx%dv%sP%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
   return ffi.C[funcNm]
end

-- select functions to compute surface EM field acceleration  terms (output is a table of functions)
function _M.selectSurfElcMag(basisNm, CDIM, VDIM, polyOrder)
   if VDIM == 1 then
      local funcNmX = string.format("VlasovSurfElcMag%dx%dv%s_VX_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      return { ffi.C[funcNmX], nullFunc, nullFunc }
   elseif VDIM == 2 then
      local funcNmX = string.format("VlasovSurfElcMag%dx%dv%s_VX_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      local funcNmY = string.format("VlasovSurfElcMag%dx%dv%s_VY_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      return { ffi.C[funcNmX], ffi.C[funcNmY], nullFunc }
   elseif VDIM == 3 then
      local funcNmX = string.format("VlasovSurfElcMag%dx%dv%s_VX_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      local funcNmY = string.format("VlasovSurfElcMag%dx%dv%s_VY_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      local funcNmZ = string.format("VlasovSurfElcMag%dx%dv%s_VZ_P%d", CDIM, VDIM, basisNmMap[basisNm], polyOrder)
      return { ffi.C[funcNmX], ffi.C[funcNmY], ffi.C[funcNmZ] }
   end
end


return _M
