add_executable(11 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(11 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(11 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(11 PROPERTIES OUTPUT_NAME main)