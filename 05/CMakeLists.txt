add_executable(05 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(05 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(05 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(05 PROPERTIES OUTPUT_NAME main)