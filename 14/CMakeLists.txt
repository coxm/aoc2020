add_executable(14 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(14 PRIVATE ${aoc_CXX_FLAGS})
target_compile_definitions(14 PRIVATE
  -DDEFAULT_INPUT_FILE="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_target_properties(14 PROPERTIES OUTPUT_NAME main)


if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  string(REPLACE "." ";" GCC_VERSION ${CMAKE_CXX_COMPILER_VERSION})
  list(GET GCC_VERSION 0 GCC_MAJOR)
  list(GET GCC_VERSION 1 GCC_MINOR)
  list(GET GCC_VERSION 2 GCC_PATCH)
  if(${GCC_MAJOR} LESS "10")
    message(STATUS "Using std::floor2 instead of std::bit_floor")
    target_compile_definitions(14 PRIVATE -DFLOOR2=1)
  endif()
endif()
