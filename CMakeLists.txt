cmake_minimum_required(VERSION 3.15)

set(CXX_STANDARD 17)

set(HEADER_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)


set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src)