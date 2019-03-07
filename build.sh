#!bin/sh

echo -e "\033[32m
1 - Built with Clang\n
2 - Built with GNU\033[0m"

read chs

case $chs in 

1*)
rm -rf build
mkdir build
cd build
export CC=/usr/bin/cc
export CXX=/usr/bin/c++
cmake ../ && make all
;;

2*)
rm -rf build
mkdir build
cd build
export CC=/usr/local/bin/gcc
export CXX=/usr/local/bin/g++
cmake ../ && make all
;;
esac

