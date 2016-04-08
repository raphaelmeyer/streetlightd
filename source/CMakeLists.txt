
cmake_minimum_required (VERSION 3.1)
project (Main)


set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 14)
add_definitions(-DNO_LOGGING)
#include_directories ("${PROJECT_SOURCE_DIR}/amqp/")
include_directories ("${PROJECT_SOURCE_DIR}/mqtt/")
include_directories ("${PROJECT_SOURCE_DIR}/dbus/")
include_directories ("${PROJECT_SOURCE_DIR}/presentation/")
include_directories ("${PROJECT_SOURCE_DIR}/session/")
include_directories ("${PROJECT_SOURCE_DIR}/application/")

include_directories("$(PROJECT_BINARY_DIR)")
include_directories("/usr/include/dbus-c++-1")

file(GLOB RAW_SOURCES
    session/*.cpp
    dbus/*.cpp
    presentation/*.cpp
    application/*.cpp
    )

add_executable(Streetlightd main.cpp ${RAW_SOURCES})

target_link_libraries( Streetlightd mosquittopp dbus-c++-1 pthread) 

set(EXECUTABLE_OUTPUT_PATH "../")
