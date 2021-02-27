project(Temp)

add_library(Temp STATIC TemperatureManager.cpp TempSensor.cpp)

target_link_libraries(Temp PUBLIC Dispatcher)

target_include_directories(Temp PUBLIC
							"${PROJECT_SOURCE_DIR}/../"
						  )