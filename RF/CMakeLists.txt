project(RF)
add_library(RF SHARED main.cpp)

target_include_directories(RF PUBLIC
							"${PROJECT_SOURCE_DIR}/../lib/wiringpi"
						  )