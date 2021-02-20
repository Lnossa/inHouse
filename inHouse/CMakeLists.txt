project(inHouse)
message("${PROJECT_SOURCE_DIR}")
add_executable(inHouse main.cpp)

add_library(wipi SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(bar PROPERTIES
  IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../lib/wiringpi/libwiringPi.so"
  INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/../lib/wiringpi/"
)

target_link_libraries(inHouse PUBLIC 
	Logger
	$<TARGET_OBJECTS:Dispatcher>
	$<TARGET_OBJECTS:IR>
	$<TARGET_OBJECTS:LCD>
	$<TARGET_OBJECTS:MQTT>
	RF
	$<TARGET_OBJECTS:Temp>
	$<TARGET_OBJECTS:Utils>
	pthread
	wipi
	mosquittopp
	curl
	jsoncpp
)

target_include_directories(inHouse PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )
						  

