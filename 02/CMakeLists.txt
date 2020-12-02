add_executable(02 "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_compile_options(02 PRIVATE ${aoc_CXX_FLAGS})
set_target_properties(02 PROPERTIES OUTPUT_NAME main)
target_compile_definitions(02 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
