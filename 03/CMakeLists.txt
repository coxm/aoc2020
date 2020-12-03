add_executable(03 "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_compile_options(03 PRIVATE ${aoc_CXX_FLAGS})
set_target_properties(03 PROPERTIES OUTPUT_NAME main)
target_compile_definitions(03 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
