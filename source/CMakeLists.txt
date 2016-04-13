
cmake_minimum_required (VERSION 3.1)
project (Main)


set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_definitions(-DNO_LOGGING)
include_directories ("${PROJECT_SOURCE_DIR}/amqp/")
include_directories ("${PROJECT_SOURCE_DIR}/mqtt/")
include_directories ("${PROJECT_SOURCE_DIR}/dbus/")
include_directories ("${PROJECT_SOURCE_DIR}/presentation/")
include_directories ("${PROJECT_SOURCE_DIR}/session/")
include_directories ("${PROJECT_SOURCE_DIR}/application/")

include_directories("$(PROJECT_BINARY_DIR)")
include_directories(".")
include_directories("/usr/include/dbus-c++-1")

include_directories ("amqp/azure-iot-sdks/c/iothub_client/inc/")
include_directories ("amqp/azure-iot-sdks/c/azure-uamqp-c/azure-c-shared-utility/c/inc/")

add_subdirectory("${PROJECT_SOURCE_DIR}/amqp/")

file(GLOB RAW_SOURCES
    *.h
    protocolstack/*.h
    protocolstack/*.cpp
    protocolstack/session/*.cpp
    protocolstack/session/*.h
    dbus/*.cpp
    protocolstack/presentation/*.cpp
    protocolstack/presentation/*.h
    protocolstack/application/*.cpp
    protocolstack/application/*.h
    infrastructure/*.cpp
    infrastructure/*.h
    amqp/AmqpSession.cpp
    )

file(GLOB_RECURSE TEST_SOURCES
    *_Test.cpp
    *_Mock.h
    infrastructure/CommandLineParser.cpp
    infrastructure/Factory.h
    protocolstack/application/Forwarder.cpp
    protocolstack/presentation/KeyValueEncoder.cpp
    protocolstack/presentation/KeyValueDecoder.cpp
    protocolstack/presentation/JsonEncoder.cpp
    protocolstack/presentation/JsonDecoder.cpp
    )

add_executable(streetlightd main.cpp ${RAW_SOURCES})
target_link_libraries(streetlightd mosquittopp dbus-c++-1 pthread PocoUtil jsoncpp PocoNet PocoNetSSL PocoFoundation iothub_client iothub_client_amqp_transport uamqp ssl crypto)

add_executable(unit-test ${TEST_SOURCES})
target_link_libraries(unit-test gmock_main pthread PocoUtil jsoncpp)

set(EXECUTABLE_OUTPUT_PATH "../")
