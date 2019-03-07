set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -pipe -msse2 -mssse3 -m32 -fno-exceptions --std=c++1z --stdlib=libc++ -DCRYPTOPP_DISABLE_ASM")
set(SOURCE
src/AsyncSQL.cpp
src/Semaphore.cpp
src/Statement.cpp
src/Tellwait.cpp
include/AsyncSQL.h
include/libsql.h
include/Semaphore.h
include/Statement.h
include/stdafx.h
include/Tellwait.h
)
include_directories(include)
add_library(libsql STATIC ${SOURCE})