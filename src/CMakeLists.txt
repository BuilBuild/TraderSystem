
include_directories(${HEADER_DIR})


aux_source_directory(. SRC)



add_executable(main ${SRC})