include_directories(${HEADER_DIR})

message(-abaaa- ${HEADER_DIR})

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(test_data_get test_data_get.cpp)
target_link_libraries(test_data_get TraderSystem_base)