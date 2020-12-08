cmake_minimum_required(VERSION 3.17)
project(aoc-2020 LANGUAGES CXX VERSION 0.0.0)


set(CMAKE_CXX_STANDARD 20)
list(APPEND aoc_CXX_FLAGS -Werror -std=c++1z -Wall -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wno-pmf-conversions -Wshadow -Wmaybe-uninitialized)
if(CMAKE_COMPILER_IS_GNUCXX)
  list(APPEND aoc_CXX_FLAGS -Weffc++)
endif()


add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)
add_subdirectory(08)
