project(inHouse)
message("${PROJECT_SOURCE_DIR}")
add_executable(inHouse main.cpp)

target_link_libraries(inHouse PUBLIC 
	Logger
	$<TARGET_OBJECTS:Dispatcher>
	$<TARGET_OBJECTS:libIR>
	$<TARGET_OBJECTS:LCD>
	$<TARGET_OBJECTS:MQTT>
	RF
	$<TARGET_OBJECTS:Temp>
	$<TARGET_OBJECTS:Utils>
	pthread
	wiringPi
	mosquittopp
	curl
	jsoncpp
)

target_include_directories(inHouse PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )

target_compile_options(inHouse PRIVATE "-Wall;-Werror")