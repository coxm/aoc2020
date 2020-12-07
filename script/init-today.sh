day="${day:-$( date +"%d" )}"
mkdir -p $day

echo -n -e "add_executable($day \${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options($day PRIVATE \${aoc_CXX_FLAGS})
target_compile_definitions($day PRIVATE
  -DDEFAULT_INPUT_FILE=\"\${CMAKE_CURRENT_SOURCE_DIR}/input.txt\")
set_target_properties($day PROPERTIES OUTPUT_NAME main)" > $day/CMakeLists.txt


echo "add_subdirectory($day)" >> CMakeLists.txt
