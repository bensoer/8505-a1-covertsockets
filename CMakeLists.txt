cmake_minimum_required(VERSION 3.6)
project(8505_a1_covertsockets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES src/main.cpp src/utils/argparser.h src/EndpointFactory.cpp src/EndpointFactory.h src/IEndpoint.cpp src/IEndpoint.h src/ClientEndpoint.cpp src/ClientEndpoint.h src/ServerEndpoint.cpp src/ServerEndpoint.h)
add_executable(8505_a1_covertsockets ${SOURCE_FILES})