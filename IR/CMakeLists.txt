project(IR)
add_library(libIR STATIC IRManager.cpp IRDriver.cpp)

target_link_libraries(libIR Dispatcher)