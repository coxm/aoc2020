#include <cassert>
#include <memory>
#include <algorithm>
#include <iostream>
#include <fstream>


int main(int const argc, char const* const* const argv) {
  char const* filepath = argc < 2 ? DEFAULT_INPUT_FILE : argv[1];
  std::ifstream file(filepath);

  unsigned partOne = 0;
  unsigned partTwo = 0;
  while (file.good()) {
    int low = 0;
    int high = 0;
    char chr = '\0';
    std::string password;
    file >> low;
    if (file.eof()) {
      break;
    }
    assert(file.get() == '-');
    file >> high;
    assert(file.get() == ' ');
    file >> chr;
    assert(file.get() == ':');
    assert(file.get() == ' ');
    file >> password;

    // Part one.
    auto const occurrences = std::count(password.begin(), password.end(), chr);
    if (low <= occurrences && occurrences <= high) {
      ++partOne;
    }

    // Part two.
    auto const isInFirst = password[low - 1] == chr;
    auto const isInSecond = password[high - 1] == chr;
    if (isInFirst xor isInSecond) {
      ++partTwo;
    }
  }

  std::cout << "Part one: " << partOne << std::endl;
  std::cout << "Part two: " << partTwo << std::endl;

  return EXIT_SUCCESS;
}
