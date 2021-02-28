project(Utils)
add_library(Utils STATIC)

target_sources(Utils PRIVATE
	Date.cpp
	HTTP.cpp
	Weather.cpp
)
