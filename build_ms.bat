@echo off

set CC=C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-gcc.exe
set CXX=C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-g++.exe

cd Build
cmake ../ -G "Unix Makefiles" 
make
cd ..