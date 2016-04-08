cmake_minimum_required (VERSION 3.1)
project (AMQPConnection)


set (AMQPConnection_VERSION_MAJOR 0)
set (AMQPConnection_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 14)
add_definitions(-DNO_LOGGING)
include_directories ("${PROJECT_SOURCE_DIR}/../presentation/")
add_subdirectory ("${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/" EXCLUDE_FROM_ALL)
#add_subdirectory ("${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/iothub_client")
#add_subdirectory ("${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/azure-uamqp-c/")
#add_subdirectory ("${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/iothub_client/")
#add_subdirectory("${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/azure-uamqp-c/azure-c-shared-utility/c/")
include_directories ("${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/iothub_client/inc/")
include_directories ("${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/azure-uamqp-c/azure-c-shared-utility/c/inc/")


# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
#  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#  )


include_directories("$(PROJECT_BINARY_DIR)")

add_executable(AMQPSession AMQPSession.cpp main.cpp)
#add_library(iothub_client STATIC IMPORTED)
target_include_directories(AMQPSession PUBLIC "${PROJECT_SOURCE_DIR}/azure-iot-sdks/c/")
target_link_libraries( AMQPSession aziotsharedutil iothub_client iothub_client_amqp_transport uamqp ssl crypto)
#target_link_libraries(AMQPConnection aziotsharedutil ssl crypto)
