cmake_minimum_required(VERSION 3.0)
project(gptbackend VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PREG_PARSER_SOURCES
	preg/preg_data.cpp
	preg/preg_parser.cpp
)

set(GPTBACKEND_SOURCES
	main.cpp
)

# Definitions for configuration file
configure_file("config.h.in" "config.h")

add_executable(gptbackend
	${GPTBACKEND_SOURCES}
	${PREG_PARSER_SOURCES}
)
target_include_directories(gptbackend
	PUBLIC
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/preg/include
)

install(TARGETS gptbackend RUNTIME DESTINATION ${CMAKE_BINARY_DIR})
