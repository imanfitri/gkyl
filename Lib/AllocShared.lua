-- Gkyl ------------------------------------------------------------------------
--
-- Allocator for memory that is shared between processes. The
-- processes must live on a communicator created using MPI-SHM calls.
-- 
--    _______     ___
-- + 6 @ |||| # P ||| +
--------------------------------------------------------------------------------

-- system libraries
local ffi  = require "ffi"
local xsys = require "xsys"
local new, copy, fill, sizeof, typeof, metatype = xsys.from(ffi,
     "new, copy, fill, sizeof, typeof, metatype")

-- Gkyl libraries
local Mpi = require "Comm.Mpi"

-- Wrapper around MPI memory functions
local function sharedAlloc(comm, sz)
   -- Allocate memory on rank 0 only, attaching handles to this on all
   -- other ranks. Hence, all ranks have direct access to all the
   -- allocated memory. The communicate 'comm' must be of type
   -- MPI_COMM_TYPE_SHARED

   local data, win = nil, nil
   local ssz, du
   if Mpi.Comm_rank(comm) == 0 then
      -- allocate all memory on rank 0
      data, win = Mpi.Win_allocate_shared(sz, 1, Mpi.INFO_NULL, comm)
   else
      -- note 0 size; call must be made as this is a collective call
      data, win = Mpi.Win_allocate_shared(0, 1, Mpi.INFO_NULL, comm)
      ssz, du, data = Mpi.Win_shared_query(win, 0) -- get handle to rank-0 array location
   end
   
   return data, win
end
local function sharedFree(win, d)
   Mpi.Win_free(win) -- DOES THIS REALLY FREE THE MEMORY ALSO?!
end


-- AllocShared -----------------------------------------------------------------
--
-- A 1D shared array on MPI-SHM communicator
--------------------------------------------------------------------------------

local function AllocShared_meta_ctor(elct)
   local elmSz = sizeof(elct) -- element size in bytes

   -- copy function for non-numeric types: this is used in methods
   -- that set array values if the element type stored is not numeric
   local isNumberType = false
   local copyElemFunc = nil
   if ffi.istype(new(elct), new("double")) then
      isNumberType = true
   elseif ffi.istype(new(elct), new("float")) then
      isNumberType = true
   elseif ffi.istype(new(elct), new("int")) then
      isNumberType = true
   else
      -- AT PRESENT NOT SUPPORTING NON-NUMERIC TYPES
      assert(false, "AllocShared_meta_ctor: Non-numeric type not supported yet!")
      isNumberType = false
      copyElemFunc = function (dst, src) ffi.copy(dst, src, elmSz) end      
   end

   -- Allocate memory using MPI-SHM calls. PERHAPS I NEED TO ZERO OUT
   -- THE ALLOCATED MEMORY?
   local function alloc(ct, comm, num)
      local v = new(ct)
      v._size = num
      v._data, v._win = sharedAlloc(comm, elmSz*num)

      local rnk = Mpi.Comm_rank(comm)
      local nr = Mpi.Comm_size(comm)
      -- calculate local range of owned indices
      local baseShape = math.floor(num/nr)
      local remCells = num % nr -- extra cells left over

      local shape, start = {}, {}
      for c = 1, nr do
      	 shape[c] = baseShape + (remCells>0 and 1 or 0) -- add extra cell if any remain
      	 remCells = remCells-1
      end
      start[1] = 1
      for c = 2, nr do
      	 start[c] = start[c-1]+shape[c-1]
      end
      v._s, v._e = start[rnk+1], start[rnk+1]+shape[rnk+1]-1
      
      return v
   end

   local alloc_funcs = {
      elemType = function (self)
	 return elct
      end,
      elemSize = function (self)
	 return sizeof(elct)
      end,
      data = function (self)
	 return self._data
      end,      
      size = function(self)
	 return self._size
      end,
      localSize = function (self)
	 return self._e-self._s+1
      end,
      lower = function (self)
	 return self._s
      end,
      upper = function (self)
	 return self._e
      end,      
      delete = function (self)
	 sharedFree(self._win, self._data)
      end,
   }
   local alloc_mt = {
      __new = function (ct, comm, num)
	 if num then
	    return alloc(ct, comm, num)
	 else
	    return alloc(ct, comm, 0)
	 end
      end,
      __index = function (self, k)
	 if type(k) == "number" then
	    return self._data[k-1]
	 else
	    return alloc_funcs[k]
	 end
      end,
      __newindex = function (self, k, v)
	    self._data[k-1] = v
	 end,
      __gc = function (self)
	 self:delete()
      end,
   }
   return metatype(typeof("struct { int32_t _size; int32_t _s, _e; MPI_Win *_win; $* _data; }", elct), alloc_mt)
end

-- function to create an allocator for custom type
local function createAllocator(typeStr)
   return AllocShared_meta_ctor(ffi.typeof(typeStr))
end

return {
   AllocShared_meta_ctor = AllocShared_meta_ctor,
   Double = createAllocator("double"),
   Float = createAllocator("float"),
   Int = createAllocator("int"),
}
