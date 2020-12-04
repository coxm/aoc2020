add_executable(04 "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_compile_options(04 PRIVATE ${aoc_CXX_FLAGS})
set_target_properties(04 PROPERTIES OUTPUT_NAME main)
target_compile_definitions(04 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  target_compile_definitions(04 PRIVATE -DVERBOSE=1)
endif()
