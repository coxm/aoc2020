#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <iostream>


unsigned
stou(std::string const& input) {
  auto i = std::stoul(input);
  if (i > std::numeric_limits<unsigned>::max()) {
    throw std::out_of_range(input);
  }
  return unsigned(i);
}


template <typename Iter, unsigned N>
unsigned
multiplySummableTo(Iter begin, Iter end, unsigned sum) {
  if constexpr(N == 0) {
    return 0;
  }

  if constexpr(N == 1) {
    for (; begin != end; ++begin) {
      if (*begin == sum) {
        return sum;
      }
    }
    return 0;
  }

  if constexpr(N > 1) {
    for (; begin != end; ++begin) {
      unsigned product =
        multiplySummableTo<Iter, N - 1>(begin, end, sum - *begin);
      if (product != 0) {
        return *begin * product;
      }
    }
    return 0;
  }
}


int main(int const argc, char const* const* argv) {
  char const* filepath = argc < 2 ? DEFAULT_INPUT_FILE : argv[1];
  std::ifstream ifs(filepath);
  std::vector<unsigned> entries;
  while (ifs.good()) {
    int tmp;
    ifs >> tmp;
    entries.push_back(tmp);
  }

  using Iterator = decltype(entries)::iterator;
  auto const part1 = multiplySummableTo<Iterator, 2u>(
      entries.begin(), entries.end(), 2020);
  auto const part2 = multiplySummableTo<Iterator, 3u>(
      entries.begin(), entries.end(), 2020);

  std::cout << "Part 1: " << part1 << std::endl;
  std::cout << "Part 2: " << part2 << std::endl;
  return EXIT_SUCCESS;
}
