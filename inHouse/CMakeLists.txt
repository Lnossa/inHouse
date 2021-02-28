project(inHouse)
message("${PROJECT_SOURCE_DIR}")
add_executable(inHouse main.cpp)

target_link_libraries(inHouse 
	Dispatcher
	libIR
	LCD
	MQTT
	RF
	Temp
	Utils
	pthread
	wiringPi
	mosquittopp
	curl
	jsoncpp
)