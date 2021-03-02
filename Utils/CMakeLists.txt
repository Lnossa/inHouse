project(Utils)
add_library(Utils STATIC)

target_sources(Utils PRIVATE
	Date.cpp
	HTTP.cpp
	Weather.cpp
)

target_include_directories(Utils PUBLIC
						  "${PROJECT_SOURCE_DIR}/../"
						  )