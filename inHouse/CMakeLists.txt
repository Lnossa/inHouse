project(inHouse)
message("${PROJECT_SOURCE_DIR}")
add_executable(inHouse main.cpp)

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
wiringPi
)

set_property(TARGET inHouse PROPERTY
  VS_PACKAGE_REFERENCES "jsoncpp_0.6.0.1")

target_include_directories(inHouse PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  "C:/SysGCC/raspberry/arm-linux-gnueabihf/sysroot/usr/include/"
						  #"${PROJECT_SOURCE_DIR}/packages/jsoncpp.0.6.0.1/build/native/include/"
						  "${PROJECT_SOURCE_DIR}/packages/curl.7.30.0.2/build/native/include/"
						  "${PROJECT_SOURCE_DIR}/packages/mosquittopp.1.0.2/include")
						  

