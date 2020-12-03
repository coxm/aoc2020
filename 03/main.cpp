#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>


template <typename RandomAccessIter>
std::uint64_t
countTrees(
  RandomAccessIter begin, RandomAccessIter end,
  std::uint64_t width, std::uint64_t height,
  std::uint64_t dx, std::uint64_t dy
) {
  std::uint64_t sum = 0;
  for (std::uint64_t row = 0, col = 0;
       row < height;
       row += dy, col = (col + dx) % width
  ) {
    std::uint64_t index = row * width + col;
    auto const it = begin + index;
    bool const isTree = *it;
    sum += isTree;
  }
  return sum;
}


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  if (!ifs.good()) {

  }

  unsigned width = 0;
  unsigned height = 0;
  std::vector<bool> trees;
  for (std::string line; std::getline(ifs, line); ++height) {
    width = std::max(unsigned(line.size()), width);
    std::transform(
      std::begin(line), std::end(line), std::back_inserter(trees),
      [](char c) {
        return c == '#';
      }
    );
  }

  auto const multiples = {
    countTrees(std::begin(trees), std::end(trees), width, height, 1, 1),
    countTrees(std::begin(trees), std::end(trees), width, height, 3, 1),
    countTrees(std::begin(trees), std::end(trees), width, height, 5, 1),
    countTrees(std::begin(trees), std::end(trees), width, height, 7, 1),
    countTrees(std::begin(trees), std::end(trees), width, height, 1, 2)
  };

  {
    auto it = multiples.begin();
    std::cout << "Part one: " << *(++it) << std::endl;
  }

  {
    auto it = multiples.begin();
    std::uint64_t product = *it;
    std::cout << "Part two: " << *it;
    while (++it != multiples.end()) {
      std::cout << " * " << *it;
      product *= *it;
    }
    std::cout << " = " << product << std::endl;
  }
  return 0;
}
