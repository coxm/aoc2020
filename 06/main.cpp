#include <cstdint>
#include <iostream>
#include <fstream>


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);

  unsigned partOne = 0;
  unsigned partTwo = 0;
  while (ifs.good()) { // Each group.
    // Questions are all marked a-z, so a uint32_t (and ASCII-only!) is fine.
    std::uint32_t groupAnswers[26] = {0};
    unsigned groupSize = 1;

    while (ifs.good()) { // Each person.
      char const question = ifs.get();
      if (question != '\n') {
        ++groupAnswers[question - 'a'];
        continue;
      }

      if (ifs.peek() == '\n') {
        // Group complete.
        ifs.get();
        break;
      }
      if (ifs.peek() == std::ifstream::traits_type::eof()) {
        // EOF.
        break;
      }

      // Next person in group to follow.
      ++groupSize;
    }

    for (unsigned question = 0; question < 26; ++question) {
      partOne += (groupAnswers[question] != 0);
      partTwo += (groupAnswers[question] == groupSize);
    }
  }

  std::cout << "Part one: " << partOne << "\nPart two: " << partTwo
    << std::endl;
  return 0;
}
