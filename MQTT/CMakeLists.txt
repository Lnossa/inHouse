project(MQTT)
add_library(MQTT STATIC)


target_sources(MQTT PRIVATE
    MQTTManager.cpp
    MQTT.cpp
)

target_link_libraries(MQTT PRIVATE Dispatcher)
						  
target_compile_options(MQTT PUBLIC "-Wno-deprecated-declarations")