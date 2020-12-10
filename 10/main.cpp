#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <unordered_map>


using joltage_type = unsigned;
using count_type = unsigned long;


struct Link {
  // joltage_type sum;
  joltage_type previous;
  joltage_type diff1Count;
  joltage_type diff3Count;
};


struct PairHash {
  constexpr std::size_t
  operator()(std::pair<joltage_type, joltage_type> val) const noexcept {
    if constexpr(sizeof(std::size_t) >= 2 * sizeof(joltage_type)) {
      return (std::size_t(val.first) << sizeof(joltage_type)) | val.second;
    }

    // Cantor pairing function.
    return val.second +
      ((val.first + val.second) * (val.first + val.second + 1)) / 2;
  }
};


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
    auto const chain = std::accumulate(
      std::begin(adaptors) + 1,
      std::end(adaptors),
      Link{0, 0, 1}, // diff3Count starts at 1 because of the device.
      [] (Link const& link, joltage_type const joltage) -> Link {
        return Link{
          // link.sum + joltage - link.previous,
          joltage,
          link.diff1Count + joltage_type(joltage - link.previous == 1),
          link.diff3Count + joltage_type(joltage - link.previous == 3)
        };
      }
    );
    std::cout << "Part one: " << chain.diff1Count * chain.diff3Count
      << std::endl;
  }


  { // Part two.
    std::unordered_map<
      std::pair<joltage_type, joltage_type>,
      count_type,
      PairHash
    > counts;

    joltage_type const deviceJoltage = adaptors.back() + 3;
    for (int len = int(adaptors.size()), i = len - 1; i >= 0; --i) {
      auto const currentJoltage = adaptors[i];
      auto const currentReach = currentJoltage + 3;
      auto arrangements = count_type(currentReach >= deviceJoltage);
      for (int j = i + 1; j < len; ++j) {
        joltage_type const stepJoltage =  adaptors[j];
        if (stepJoltage > currentReach) {
          break;
        }
        auto const key = std::make_pair(stepJoltage, deviceJoltage);
        auto const emplaceResult = counts.try_emplace(key, 0);
        arrangements += emplaceResult.first->second;
      }
      counts.try_emplace(
        std::make_pair(currentJoltage, deviceJoltage), arrangements);
    }

    std::cout << "Part two: " << counts[std::make_pair(0, deviceJoltage)]
      << std::endl;
  }

  return 0;
}
