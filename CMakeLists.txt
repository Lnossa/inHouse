cmake_minimum_required(VERSION 3.5)

cmake_policy(SET CMP0076 NEW)

#set compiler
set(CMAKE_C_COMPILER "C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-gcc.exe")
set(CMAKE_CXX_COMPILER "C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-g++.exe")

set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# set the project name
project(inHouse)

#add libraries
add_subdirectory(Logger)
add_subdirectory(Utils)
add_subdirectory(Dispatcher)
add_subdirectory(IR)
add_subdirectory(LCD)
add_subdirectory(MQTT)
add_subdirectory(RF)
add_subdirectory(Temp)
add_subdirectory(inHouse)

# add the binary tree to the search path for include files
target_include_directories(Logger PUBLIC
                          "${PROJECT_BINARY_DIR}"
						  "${PROJECT_SOURCE_DIR}"
						  "${PROJECT_SOURCE_DIR}/packages/jsoncpp.0.6.0.1/build/native/include/"
						  "${PROJECT_SOURCE_DIR}/packages/curl.7.30.0.2/build/native/include/"
						  "${PROJECT_SOURCE_DIR}/packages/mosquittopp.1.0.2/include"
                          )
						  