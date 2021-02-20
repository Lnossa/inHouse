@echo off

set CMAKE_C_COMPILER=C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-gcc.exe
set CMAKE_CXX_COMPILER=C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-g++.exe

cd Build
cmake ../ -G "Unix Makefiles" 
make
cd ..