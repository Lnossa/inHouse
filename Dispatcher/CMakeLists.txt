project(Dispatcher)
add_library(Dispatcher OBJECT)

target_sources(Dispatcher PUBLIC
Dispatcher.cpp
ModuleBase.cpp
Msg.cpp
Msg_IncomingMQTT.cpp
Msg_IRCmd.cpp
Msg_UpdateTemperatureInfo.cpp
Msg_UpdateWeather.cpp
)


target_link_libraries(Dispatcher PUBLIC Logger)

target_include_directories(Dispatcher PUBLIC
						  "${PROJECT_SOURCE_DIR}/../")
