project(LCD)
add_library(LCD STATIC LCDManager.cpp LCD.cpp)

target_link_libraries(LCD PUBLIC 
Dispatcher
Utils
)

target_include_directories(LCD PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )