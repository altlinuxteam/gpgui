cmake_minimum_required(VERSION 3.0)
project(gpgui VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(libgptbackend)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(GPGUI_GUI_SOURCES
	gui/MainWindow.cpp
)

set(GPGUI_SOURCES
	main.cpp
	Runner.cpp
	gpgui.qrc
)

# Definitions for configuration file
set(GPGUI_APPLICATION_NAME "GPGUI")
set(GPGUI_APPLICATION_DISPLAY_NAME "GPGUI")
set(GPGUI_ORGANIZATION "BaseALT")
set(GPGUI_ORGANIZATION_DOMAIN "basealt.ru")

configure_file("config.h.in" "config.h")

add_definitions(${QT5_DEFINITIONS})
add_executable(gpgui
	${GPGUI_SOURCES}
	${GPGUI_GUI_SOURCES}
)
target_link_libraries(gpgui
	Qt5::Core
	Qt5::Widgets

	gptbackend
)
target_include_directories(gpgui
	PUBLIC
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/gui/include
)

install(TARGETS gpgui RUNTIME DESTINATION ${CMAKE_BINARY_DIR})

