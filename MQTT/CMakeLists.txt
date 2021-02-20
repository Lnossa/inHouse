project(MQTT)
add_library(MQTT OBJECT)


target_sources(MQTT PUBLIC
MQTTManager.cpp
MQTT.cpp
)

target_link_libraries(MQTT PUBLIC $<TARGET_OBJECTS:Dispatcher>)


target_include_directories(MQTT PUBLIC 
						   "${PROJECT_SOURCE_DIR}/../"
						   "${PROJECT_SOURCE_DIR}/../lib/wiringpi"
						  )