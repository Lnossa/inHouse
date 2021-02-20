project(Utils)
add_library(Utils OBJECT)

target_sources(Utils PUBLIC
Date.cpp
HTTP.cpp
Weather.cpp
)

target_link_libraries(Utils PUBLIC Logger)

set_property(TARGET Utils PROPERTY
  VS_PACKAGE_REFERENCES "jsoncpp_0.6.0.1")

target_include_directories(Utils PUBLIC
	"${PROJECT_SOURCE_DIR}/../"
	#"C:/SysGCC/raspberry/arm-linux-gnueabihf/sysroot/usr/include/"
	#"${PROJECT_SOURCE_DIR}/../packages/jsoncpp.0.6.0.1/build/native/include/"
	"${PROJECT_SOURCE_DIR}/../packages/curl.7.30.0.2/build/native/include/")
	
