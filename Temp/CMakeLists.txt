project(Temp)

add_library(Temp STATIC TemperatureManager.cpp TempSensor.cpp)

target_link_libraries(Temp PUBLIC Dispatcher)
