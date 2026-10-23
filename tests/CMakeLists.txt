add_executable(memory_tests test_memory.cpp ../src/memory.cpp)

target_include_directories(memory_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_test(NAME test_mem_file_stream COMMAND memory_tests 1)