add_executable(08 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(08 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(08 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(08 PROPERTIES OUTPUT_NAME main)