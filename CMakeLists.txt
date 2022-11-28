cmake_minimum_required(VERSION 3.24)

project (SimpleTransfer)

set(SRC_COMMON
    Platform.cpp)

set(SRC_CLIENT
    SimpleTransferClient.cpp)

set(SRC_SERVER
    SimpleTransferServer.cpp)

add_definitions("/std:c++20")

add_library(SimpleTransferCommon ${SRC_COMMON})
add_executable(SimpleTransferClient ${SRC_CLIENT})
add_executable(SimpleTransferServer ${SRC_SERVER})

target_link_libraries(SimpleTransferClient SimpleTransferCommon)
target_link_libraries(SimpleTransferServer SimpleTransferCommon)

if(WIN32)
    target_link_libraries(SimpleTransferClient ws2_32)
    target_link_libraries(SimpleTransferServer ws2_32)
endif()