project(Utils)
add_library(Utils STATIC)

target_sources(Utils PUBLIC
	Date.cpp
	HTTP.cpp
	Weather.cpp
)

# target_link_libraries(Utils PUBLIC 
	# Logger
# )

target_include_directories(Utils PUBLIC
							"${PROJECT_SOURCE_DIR}/../"
						  )
	
