cmake_minimum_required (VERSION 3.1)
project (Streetlightd)


set (Streetlightd_VERSION_MAJOR 0)
set (Streetlightd_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 14)
add_definitions(-DNO_LOGGING)
add_subdirectory ("${PROJECT_SOURCE_DIR}/source")
