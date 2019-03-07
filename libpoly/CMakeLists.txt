set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -pipe -msse2 -mssse3 -m32 -fno-exceptions --std=c++1z --stdlib=libc++ -DCRYPTOPP_DISABLE_ASM")
set(SOURCE
src/Base.cpp
src/main.cpp
src/Poly.cpp
src/Symbol.cpp
src/SymTable.cpp
include/Base.h
include/Constants.h
include/Poly.h
include/Symbol.h
include/SymTable.h
)
include_directories(include)
add_library(libpoly STATIC ${SOURCE})