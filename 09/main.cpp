#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>


template <typename Iter>
std::pair<long, long>
findSumInRange(Iter begin, Iter end, long target) {
  for (; begin != end; ++begin) {
    auto rhs = begin;
    for (++rhs; rhs != end; ++rhs) {
      if (*begin + *rhs == target) {
        return {std::min(*begin, *rhs), std::max(*begin, *rhs)};
      }
    }
  }
  return {-1, -1};
}


template <typename Iter>
long
partTwo(Iter begin, Iter end, long target) {
  for (; begin != end; ++begin) {
    auto subtotal = *begin;
    auto min = subtotal;
    auto max = subtotal;
    for (auto it = begin + 1; it != end && subtotal < target; ++it) {
      auto const value = *it;
      subtotal += value;
      min = std::min(min, value);
      max = std::max(max, value);
    }
    if (subtotal == target) {
      return min + max;
    }
  }
  return -1;
}


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  std::vector<long> numbers;
  while (ifs.good()) {
    long i;
    ifs >> i;
    numbers.push_back(i);
  }

  std::size_t const preambleSize = argc < 3 ? 25 : std::stoul(argv[2]);
  std::cout << "Using preamble size: " << preambleSize << std::endl;
  if (numbers.size() <= preambleSize) {
    return 1;
  }

  long invalid = -1;
  for (std::size_t i = 0, end = numbers.size() - preambleSize; i < end; ++i) {
    auto const target = numbers[i + preambleSize];
    auto const [min, max] = findSumInRange(
      std::begin(numbers) + i,
      std::begin(numbers) + i + preambleSize,
      target);
    if (min == -1) {
      invalid = target;
      break;
    }
  }

  std::cout << "Part one: " << invalid << std::endl;
  std::cout << "Part two: "
    << partTwo(std::begin(numbers), std::end(numbers), invalid) << std::endl;
  return 0;
}
