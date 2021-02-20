project(Temp)

add_library(Temp OBJECT TemperatureManager.cpp TempSensor.cpp)

target_link_libraries(Temp PUBLIC $<TARGET_OBJECTS:Dispatcher>)

target_include_directories(Temp PUBLIC
	"${PROJECT_SOURCE_DIR}/../"
	"${PROJECT_SOURCE_DIR}/../packages/jsoncpp.0.6.0.1/build/native/include/"
	"${PROJECT_SOURCE_DIR}/../packages/curl.7.30.0.2/build/native/include/")