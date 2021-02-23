cmake_minimum_required(VERSION 3.13)

cmake_policy(SET CMP0076 NEW)

#Environment
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -rdynamic -Wall -Werror -pedantic")
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

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
                          )
