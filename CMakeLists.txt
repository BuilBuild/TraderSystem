cmake_minimum_required(VERSION 3.15)

set(CXX_STANDARD 17)

add_definitions(-LOG_DEBUG)

set(HEADER_DIR 
    ${PROJECT_SOURCE_DIR}/Context
    ${PROJECT_SOURCE_DIR}/MsgHub
    ${PROJECT_SOURCE_DIR}/ThirdParty
    ${PROJECT_SOURCE_DIR}/Strategy
    ${PROJECT_SOURCE_DIR}/CommTypes
    ${PROJECT_SOURCE_DIR}/DataGet
    ${PROJECT_SOURCE_DIR}/APIS
    ${PROJECT_SOURCE_DIR}/ExecutionManageSys
    ${PROJECT_SOURCE_DIR}/OrderSys
    )

include_directories(${HEADER_DIR})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(TBB REQUIRED)
if(TBB_FOUND)
  message(STATUS "Found TBB version: ${TBB_VERSION}")
endif()

find_package(Boost REQUIRED)
if(Boost_FOUND)
  message(STATUS "Found Boost version: ${Boost_VERSION}")
endif()


aux_source_directory(./DataGet DataGet_SRC)
aux_source_directory(./Strategy Strategy_SRC)
aux_source_directory(./Context Context_SRC)
aux_source_directory(./MsgHub MsgHub_SRC)
aux_source_directory(./ExecutionManageSys ExecutionSys_SRC)
aux_source_directory(./OrderSys OrderSys)

add_library(TraderSystem_base 
    ${DataGet_SRC} 
    ${Strategy_SRC}
    ${Context_SRC}
    ${MsgHub_SRC}

    )

add_library(ExecutionSystem_base 
    ${ExecutionSys_SRC}
    ${OrderSys}
    )

target_link_libraries(TraderSystem_base TBB::tbb muduo_base zmq)

target_link_libraries(ExecutionSystem_base  TraderSystem_base)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(ExecutionManageSys)

