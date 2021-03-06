## Simple instructions to build LuaJIT 2.1
##
## NOTES: Post install you may want to delete the dynamic libraries,
## so that the static library is linked to gkyl.
##
## If "git checkout v2.1' does not work just download the ZIP file for
## LuaJIT 2.1beta1 and install that instead.

git clone http://luajit.org/git/luajit-2.0.git
cd luajit-2.0
git checkout v2.1
make PREFIX=$PREFIX 
make XCFLAGS=-DLUAJIT_ENABLE_GC64 install PREFIX=$PREFIX 
# delete dynamic libraries
cmd="rm -rf $PREFIX/lib/*lua*.dylib $PREFIX/gkylsoft/luajit/lib/*lua*.so*"
echo $cmd
$cmd
