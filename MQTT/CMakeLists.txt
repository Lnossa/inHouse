project(MQTT)
add_library(MQTT STATIC)


target_sources(MQTT PUBLIC
MQTTManager.cpp
MQTT.cpp
)

target_link_libraries(MQTT PUBLIC Dispatcher)


target_include_directories(MQTT PUBLIC 
						   "${PROJECT_SOURCE_DIR}/../"
						  )
						  
target_compile_options(MQTT PUBLIC "-Wall;-Wno-deprecated-declarations")