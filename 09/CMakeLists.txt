add_executable(09 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(09 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(09 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(09 PROPERTIES OUTPUT_NAME main)