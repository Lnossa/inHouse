project(inHouse)
message("${PROJECT_SOURCE_DIR}")
add_executable(inHouse main.cpp)

target_link_libraries(inHouse PUBLIC 
	#Logger
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

target_include_directories(inHouse PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )

target_compile_options(inHouse PRIVATE "-Wall;-Werror")