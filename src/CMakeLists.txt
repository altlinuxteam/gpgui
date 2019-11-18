cmake_minimum_required(VERSION 3.0)
project(gpgui VERSION 0.0.1)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(GPGUI_SOURCES
	main.cpp
)

configure_file("config.h.in" "config.h")

add_definitions(${QT5_DEFINITIONS})
add_executable(gpgui ${GPGUI_SOURCES})
target_link_libraries(gpgui
	Qt5::Core
	Qt5::Widgets
)
target_include_directories(gpgui
	PUBLIC
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/gui/include
)

install(TARGETS gpgui RUNTIME DESTINATION ${CMAKE_BINARY_DIR})

