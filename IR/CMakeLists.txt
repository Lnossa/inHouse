project(IR)
add_library(libIR OBJECT IRManager.cpp IRDriver.cpp)

target_link_libraries(libIR PUBLIC $<TARGET_OBJECTS:Dispatcher>)

target_include_directories(libIR PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )