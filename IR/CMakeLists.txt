project(IR)
add_library(libIR STATIC IRManager.cpp IRDriver.cpp)

target_link_libraries(libIR PUBLIC Dispatcher)

target_include_directories(libIR PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )