#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  std::vector<int> passes;
  while (ifs.good() && ifs.peek() != std::ifstream::traits_type::eof()) {
    int pass = (
      ((ifs.get() == 'B') << 9) |
      ((ifs.get() == 'B') << 8) |
      ((ifs.get() == 'B') << 7) |
      ((ifs.get() == 'B') << 6) |
      ((ifs.get() == 'B') << 5) |
      ((ifs.get() == 'B') << 4) |
      ((ifs.get() == 'B') << 3) |
      ((ifs.get() == 'R') << 2) |
      ((ifs.get() == 'R') << 1) |
      (ifs.get() == 'R')
    );
    ifs.get();
    passes.push_back(pass);
  }

  std::sort(std::begin(passes), std::end(passes));

  // std::adjacent_find makes this a bit trivial...
  auto const iYourPass = std::adjacent_find(
    std::begin(passes), std::end(passes),
    [] (int a, int b) {
      return a + 1 != b;
    }
  );
  int const yourPass = iYourPass == std::end(passes) ? -1 : (*iYourPass + 1);
  std::cout << "Part one: " << passes.back() << "\n"
            << "Part two: " << yourPass << std::endl;

  return EXIT_SUCCESS;
}
