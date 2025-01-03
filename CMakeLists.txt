cmake_minimum_required(VERSION 3.15)

set(CXX_STANDARD 17)

set(HEADER_DIR 
    ${PROJECT_SOURCE_DIR}/ThirdParty
    ${PROJECT_SOURCE_DIR}/Strategy
    ${PROJECT_SOURCE_DIR}/CommTypes
    )

include_directories(${HEADER_DIR})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(./DataGet DataGet_SRC)
aux_source_directory(./Strategy Strategy_SRC)

add_library(TraderSystem_base 
    ${DataGet_SRC} 
    ${Strategy_SRC}
    )


add_subdirectory(src)
