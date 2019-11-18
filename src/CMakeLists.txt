cmake_minimum_required(VERSION 3.0)
project(gpgui VERSION 0.0.1)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(GPGUI_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/config.h
	main.cpp
)

configure_file("config.h.in" "config.h")

add_definitions(${QT5_DEFINITIONS})
add_executable(gpgui ${GPGUI_SOURCES})
target_link_libraries(gpgui Qt5::Widgets)

install(TARGETS gpgui RUNTIME DESTINATION ${CMAKE_BINARY_DIR})

