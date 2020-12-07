add_executable(07 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(07 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(07 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(07 PROPERTIES OUTPUT_NAME main)