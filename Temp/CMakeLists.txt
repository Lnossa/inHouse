project(Temp)

add_library(Temp OBJECT TemperatureManager.cpp TempSensor.cpp)

target_link_libraries(Temp PUBLIC $<TARGET_OBJECTS:Dispatcher>)

target_include_directories(Temp PUBLIC
							"${PROJECT_SOURCE_DIR}/../"
						  )