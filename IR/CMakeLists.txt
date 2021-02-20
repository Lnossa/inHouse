project(IR)
add_library(IR OBJECT IR.cpp LED.cpp)

target_link_libraries(IR PUBLIC $<TARGET_OBJECTS:Dispatcher>)

target_include_directories(IR PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )