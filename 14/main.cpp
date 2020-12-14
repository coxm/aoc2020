#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <bit>


struct Mask {
  std::uint64_t m_eraser = 0;
  std::uint64_t m_writer = 0;
  std::uint64_t m_floats = 0;

  inline std::uint64_t operator()(std::uint64_t value) const noexcept {
    return (value & ~m_eraser) | m_writer;
  }
};


template <typename InputStream>
InputStream& operator>>(InputStream&& input, Mask& mask) {
  Mask tmp;
  input >> std::ws;

  bool parsing = true;
  for (std::uint64_t bit = 0x800000000; parsing; bit >>= 1) {
    switch (input.get()) {
      case '0':
        tmp.m_eraser |= bit;
        break;
      case '1':
        tmp.m_eraser |= bit;
        tmp.m_writer |= bit;
        break;
      case 'X':
        tmp.m_floats |= bit;
        break;
      default:
        parsing = false;
        break;
    }
  }

  mask = tmp;
  return input;
}


using Memory = std::unordered_map<std::uint64_t, std::uint64_t>;


void
writeFloatingAddresses(
  Memory& memory,
  std::uint64_t address,
  std::uint64_t floating,
  std::uint64_t value
) {
  if (floating == 0) {
    memory.insert_or_assign(address, value);
  }
  else {
    auto const bit =
#ifdef FLOOR2
      std::floor2(floating);
#else
      std::bit_floor(floating);
#endif
    floating &= ~bit;
    writeFloatingAddresses(memory, address & ~bit, floating, value);
    writeFloatingAddresses(memory, address | bit, floating, value);
  }
}


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  Mask mask;
  Memory memory1;
  Memory memory2;

  for (unsigned line = 0; ifs.good(); ++line) {
    ifs.get(); // 'm'.
    if (ifs.get() == 'a') {
      ifs.ignore(5); // "sk = "
      ifs >> mask >> std::ws;
    }
    else {
      ifs.ignore(2); // "m["
      std::uint64_t address;
      ifs >> address;
      if (address >= 0x10000) {
        std::cerr << "Address " << address << " at L" << line
          << " is too large." << std::endl;
        return 1;
      }
      ifs.ignore(4); // "] = "
      std::uint64_t value;
      ifs >> value >> std::ws;
      memory1.insert_or_assign(address, mask(value));
      address |= mask.m_writer;
      writeFloatingAddresses(memory2, address, mask.m_floats, value);
    }
  }

  std::uint64_t partOne = 0;
  for (auto const& node: memory1) {
    partOne += node.second;
  }
  std::cout << "Part one: " << partOne << std::endl;

  std::uint64_t partTwo = 0;
  for (auto const& node: memory2) {
    partTwo += node.second;
  }
  std::cout << "Part one: " << partTwo << std::endl;

  return 0;
}
