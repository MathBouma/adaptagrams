# Builds for Windows / Linux (On a Linux Machine)
# Run a Standard Linux build first
make distclean

mkdir -p m4
autoreconf --install --verbose
./configure
make    
env OSNAME="Linux" make -f Makefile-swig-csharp adaptagrams

make distclean

mkdir -p m4
autoreconf --install --verbose
env CPPFLAGS=-I'/usr/x86-w64-mingw32/' LDFLAGS=" -L'/usr/x86-w64-mingw32/lib/'" CXX="x86_64-w64-mingw32-g++" CC="x86_64-w64-mingw32-gcc"  ./configure ac_cv_func_malloc_0_nonnull=yes  ac_cv_func_realloc_0_nonnull=yes --enable-shared --host=x86_64-mingw64 --build=x86_64-linux-gnu
make
env CPPFLAGS=-I'/usr/x86-w64-mingw32/' LDFLAGS=" -L'/usr/x86-w64-mingw32/lib/'" CXX="x86_64-w64-mingw32-g++" CC="x86_64-w64-mingw32-gcc" OSNAME="MINGW32" make -f Makefile-swig-csharp
