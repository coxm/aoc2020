add_executable(13 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(13 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(13 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(13 PROPERTIES OUTPUT_NAME main)