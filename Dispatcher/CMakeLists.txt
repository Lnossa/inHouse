project(Dispatcher)
add_library(Dispatcher STATIC)

target_sources(Dispatcher PRIVATE
	Dispatcher.cpp
	ModuleBase.cpp
	Msg.cpp
	Msg_IncomingMQTT.cpp
	Msg_IRCmd.cpp
	Msg_UpdateTemperatureInfo.cpp
	Msg_UpdateWeather.cpp
)

target_include_directories(Dispatcher PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )
