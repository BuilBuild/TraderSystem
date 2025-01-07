include_directories(${HEADER_DIR})

message(-abaaa- ${HEADER_DIR})

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(test_data_get test_data_get.cpp)
target_link_libraries(test_data_get TraderSystem_base thostmduserapi_se)

add_executable(context_test context_test.cpp)
target_link_libraries(context_test TraderSystem_base)

add_executable(message_hub_test message_hub_test.cpp)
target_link_libraries(message_hub_test TraderSystem_base)

add_executable(msg_hub_sub_test msg_hub_sub_test.cpp)
target_link_libraries(msg_hub_sub_test TraderSystem_base)

add_executable(ctp_api_test ctp_api_test.cpp)
target_link_libraries(ctp_api_test TraderSystem_base thostmduserapi_se)

add_executable(execution_system_test execution_system_test.cpp)
target_link_libraries(execution_system_test ExecutionSystem_base)