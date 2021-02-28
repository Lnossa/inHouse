project(LCD)
add_library(LCD STATIC LCDManager.cpp LCD.cpp)

target_link_libraries(LCD PUBLIC 
	Dispatcher
	Utils
)
