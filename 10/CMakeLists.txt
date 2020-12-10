add_executable(10 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(10 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(10 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(10 PROPERTIES OUTPUT_NAME main)