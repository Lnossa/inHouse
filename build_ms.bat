@echo off

set CMAKE_BUILD_PARALLEL_LEVEL=%NUMBER_OF_PROCESSORS%
set CC=C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-gcc.exe
set CXX=C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-g++.exe

cd Build
cmake ../ -G "Unix Makefiles" 
cmake --build . -- -Oline
cd ..