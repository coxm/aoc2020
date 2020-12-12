#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


using joltage_type = unsigned;
using count_type = unsigned long;


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  std::vector<joltage_type> adaptors{joltage_type(0)};
  while (ifs.good()) {
    joltage_type joltage;
    ifs >> joltage >> std::ws;
    adaptors.push_back(joltage);
  }

  if (adaptors.size() < 2) {
    return 1;
  }
  std::sort(std::begin(adaptors), std::end(adaptors));


  { // Part one.
    joltage_type previous = 0;
    unsigned jump1Count = 0;
    unsigned jump3Count = 1; // Start at 1 because of the "device".
    for (auto joltage: adaptors) {
      switch (joltage - previous) {
        case 1: ++jump1Count; break;
        case 3: ++jump3Count; break;
      }
      previous = joltage;
    }
    std::cout << "Part one: " << jump1Count * jump3Count << std::endl;
  }


  { // Part two.
    /// The number of jumps from an adaptor to the device.
    std::vector<count_type> jumpsToDevice(adaptors.size(), 0);

    joltage_type const deviceJoltage = adaptors.back() + 3;
    for (int len = int(adaptors.size()), i = len - 1; i >= 0; --i) {
      auto const currentJoltage = adaptors[i];
      auto const currentReach = currentJoltage + 3;
      auto numArrangements = count_type(currentReach >= deviceJoltage);
      for (int j = i + 1; j < len; ++j) {
        joltage_type const stepJoltage =  adaptors[j];
        if (stepJoltage > currentReach) {
          break;
        }
        numArrangements += jumpsToDevice[j];
      }
      jumpsToDevice[i] = numArrangements;
    }

    std::cout << "Part two: " << jumpsToDevice[0] << std::endl;
  }

  return 0;
}
