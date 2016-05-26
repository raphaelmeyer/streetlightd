
cmake_minimum_required (VERSION 3.1)
project (Main)


set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_definitions(-DNO_LOGGING)
include_directories ("${PROJECT_SOURCE_DIR}/mqtt/")
include_directories ("${PROJECT_SOURCE_DIR}/dbus/")
include_directories ("${PROJECT_SOURCE_DIR}/presentation/")
include_directories ("${PROJECT_SOURCE_DIR}/session/")
include_directories ("${PROJECT_SOURCE_DIR}/application/")

include_directories("$(PROJECT_BINARY_DIR)")
include_directories(".")
include_directories("/usr/include/dbus-c++-1")

include_directories ("protocolstack/session/amqp/azure-iot-sdks/c/iothub_client/inc/")
include_directories ("protocolstack/session/amqp/azure-iot-sdks/c/azure-uamqp-c/azure-c-shared-utility/c/inc/")

add_subdirectory ("protocolstack/session/amqp/azure-iot-sdks/c/" EXCLUDE_FROM_ALL)

file(GLOB RAW_SOURCES
    *.h
    protocolstack/*.h
    protocolstack/*.cpp
    dbus/*.cpp
    dbus/*.h
    protocolstack/presentation/*.cpp
    protocolstack/presentation/*.h
    protocolstack/application/*.cpp
    protocolstack/application/*.h
    protocolstack/application/message/*.h
    protocolstack/application/message/*.cpp
    infrastructure/*.cpp
    infrastructure/*.h
    infrastructure/cli/*.cpp
    infrastructure/cli/*.h
    infrastructure/concurrency/*.cpp
    infrastructure/concurrency/*.h
    )

file(GLOB SAS_SOURCES
    infrastructure/SasToken.cpp
    infrastructure/SasToken.h
    infrastructure/cli/PocoParser.cpp
    infrastructure/cli/PocoParser.h
    )

file(GLOB SESSION_SOURCES
    infrastructure/SasToken.cpp
    infrastructure/SasToken.h
    infrastructure/concurrency/Timer.cpp
    infrastructure/concurrency/Timer.h
    protocolstack/presentation/Message.cpp
    protocolstack/presentation/Message.h
    protocolstack/session/*.cpp
    protocolstack/session/*.h
    protocolstack/session/mqtt/*.h
    protocolstack/session/mqtt/*.cpp
    protocolstack/session/http/*.h
    protocolstack/session/http/*.cpp
    protocolstack/session/amqp/AmqpSession.cpp
    )

file(GLOB_RECURSE TEST_SOURCES
    *_Test.cpp
    *_Mock.h
    *_Dummy.h
    *_Dummy.cpp
    infrastructure/cli/PocoParser.cpp
    infrastructure/cli/Streetlightd.cpp
    infrastructure/cli/EnumOption.cpp
    infrastructure/Factory.h
    infrastructure/SasToken.cpp
    protocolstack/application/message/Outgoing.cpp
    protocolstack/application/message/Incoming.cpp
    protocolstack/application/message/Printer.cpp
    protocolstack/application/message/DebugFormat.cpp
    protocolstack/application/message/propertyNames.cpp
    protocolstack/application/message/propertyNumbers.cpp
    protocolstack/application/Forwarder.cpp
    protocolstack/application/Debug.cpp
    protocolstack/application/Offline.cpp
    protocolstack/presentation/KeyValueEncoder.cpp
    protocolstack/presentation/KeyValueParser.cpp
    protocolstack/presentation/JsonEncoder.cpp
    protocolstack/presentation/JsonParser.cpp
    protocolstack/presentation/BinaryEncoder.cpp
    protocolstack/presentation/BinaryParser.cpp
    protocolstack/presentation/Message.cpp
    protocolstack/presentation/Null.cpp
    protocolstack/presentation/Decoder.cpp
    )

add_executable(streetlightd streetlightd.cpp ${RAW_SOURCES} ${SESSION_SOURCES})
target_link_libraries(streetlightd mosquittopp dbus-c++-1 pthread PocoUtil jsoncpp PocoNet PocoNetSSL PocoFoundation iothub_client iothub_client_amqp_transport uamqp ssl crypto crypto++)

add_executable(session-test session-test.cpp ${SESSION_SOURCES})
target_link_libraries(session-test pthread mosquittopp PocoNet PocoNetSSL PocoFoundation crypto++ iothub_client iothub_client_amqp_transport uamqp ssl crypto)

add_executable(azure-sas-token azure-sas-token.cpp ${SAS_SOURCES})
target_link_libraries(azure-sas-token PocoUtil crypto++ PocoFoundation)

add_executable(unit-test ${TEST_SOURCES})
target_link_libraries(unit-test pthread PocoUtil jsoncpp crypto++ PocoFoundation)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake-findgmock)
find_package(GMock REQUIRED)
include_directories(${GMOCK_INCLUDE_DIRS})
target_link_libraries(unit-test ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH "../")
