cmake_minimum_required(VERSION 3.22)

project (SimpleTransfer)

set(SRC_COMMON
    Platform.cpp
    SimpleTransferConnection.cpp)

set(SRC_CLIENT
    SimpleTransferClient.cpp)

set(SRC_SERVER
    SimpleTransferServer.cpp)

set(SRC_TEST
    SimpleTransferTest.cpp)

add_library(SimpleTransferCommon ${SRC_COMMON})
add_executable(SimpleTransferClient ${SRC_CLIENT})
add_executable(SimpleTransferServer ${SRC_SERVER})
add_executable(SimpleTransferTest ${SRC_TEST})

set_property(TARGET SimpleTransferClient PROPERTY CXX_STANDARD 20)
set_property(TARGET SimpleTransferServer PROPERTY CXX_STANDARD 20)
set_property(TARGET SimpleTransferTest PROPERTY CXX_STANDARD 20)

target_link_libraries(SimpleTransferClient SimpleTransferCommon)
target_link_libraries(SimpleTransferServer SimpleTransferCommon)
target_link_libraries(SimpleTransferTest SimpleTransferCommon)

if(WIN32)
    target_link_libraries(SimpleTransferClient ws2_32)
    target_link_libraries(SimpleTransferServer ws2_32)
    target_link_libraries(SimpleTransferTest ws2_32)
endif()