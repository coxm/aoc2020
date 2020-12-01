add_executable(01 "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_compile_options(01 PRIVATE ${aoc_CXX_FLAGS})
set_target_properties(01 PROPERTIES OUTPUT_NAME main)
target_compile_definitions(01 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
