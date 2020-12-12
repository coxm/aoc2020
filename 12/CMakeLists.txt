add_executable(12 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(12 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(12 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(12 PROPERTIES OUTPUT_NAME main)