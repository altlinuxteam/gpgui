cmake_minimum_required(VERSION 3.0)
project(gptbackend VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 99)

link_directories(/usr/local/lib)

find_package(Iconv)

set(PREG_PARSER_SOURCES
	preg/preg_data.cpp
	preg/preg_parser.cpp
	preg/iconv_wrapper.cpp
)

set(GPTBACKEND_SOURCES
	main.cpp
)

set(TEST_GPTBACKEND_SOURCES
	test/main.cpp
)

# Definitions for configuration file
configure_file("config.h.in" "config.h")

add_executable(gptbackend_test
	${TEST_GPTBACKEND_SOURCES}
	${PREG_PARSER_SOURCES}
)

add_library(gptbackend SHARED
	${GPTBACKEND_SOURCES}
	${PREG_PARSER_SOURCES}
)

target_include_directories(gptbackend_test
	PUBLIC
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/preg/include
)

target_include_directories(gptbackend
	PUBLIC
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/preg/include
)

target_link_libraries(gptbackend_test
	${Iconv_LIBRARIES}
)

target_link_libraries(gptbackend
	${Iconv_LIBRARIES}
)

install(TARGETS gptbackend LIBRARY DESTINATION ${CMAKE_BINARY_DIR})

