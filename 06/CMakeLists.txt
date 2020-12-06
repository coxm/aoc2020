add_executable(06 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(06 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(06 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(06 PROPERTIES OUTPUT_NAME main)