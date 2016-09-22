cmake_minimum_required(VERSION 3.6)
project(8505_a1_covertsockets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES src/endpoints/EndpointFactory.cpp src/endpoints/EndpointFactory.h src/main.cpp src/utils/argparser.h src/endpoints/IEndpoint.cpp src/endpoints/IEndpoint.h src/endpoints/client/ClientEndpoint.cpp src/endpoints/client/ClientEndpoint.h src/endpoints/server/ServerEndpoint.cpp src/endpoints/server/ServerEndpoint.h src/Configuration.h)
add_executable(8505_a1_covertsockets ${SOURCE_FILES})