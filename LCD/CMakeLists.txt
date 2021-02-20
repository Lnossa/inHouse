project(LCD)
add_library(LCD OBJECT LCDManager.cpp LCD.cpp)

target_link_libraries(LCD PUBLIC 
$<TARGET_OBJECTS:Dispatcher>
$<TARGET_OBJECTS:Utils>
)

target_include_directories(LCD PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )