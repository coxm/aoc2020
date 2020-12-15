#include <cstdint>
#include <iostream>
#include <fstream>
#include <unordered_map>


using number_type = std::uint64_t;


class Info {
public:
  Info(number_type lastUsed)
    : m_before(lastUsed)
    , m_after(lastUsed)
  {
  }

  inline number_type delta(number_type turn) const noexcept {
    return m_after - m_before;
  }

  inline void speak(number_type turn) noexcept {
    m_before = m_after;
    m_after = turn;
  }

private:
  number_type m_before;
  number_type m_after;
};


using map_type = std::unordered_map<number_type, Info>;


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  map_type spoken;
  number_type number;
  number_type turn = 1;

  map_type::iterator lastSpoken;
  for (char c; ifs.good(); ++turn) {
    ifs >> number >> c >> std::ws;
    auto const result = spoken.insert_or_assign(number, turn);
    lastSpoken = result.first;
  }

  for (; turn <= 2020; ++turn) {
    number = lastSpoken->second.delta(turn);
    lastSpoken = spoken.emplace(number, turn).first;
    lastSpoken->second.speak(turn);
  }
  std::cout << "Part one: " << number << std::endl;

  for (; turn <= 30000000; ++turn) {
    number = lastSpoken->second.delta(turn);
    lastSpoken = spoken.emplace(number, turn).first;
    lastSpoken->second.speak(turn);
  }
  std::cout << "Part two: " << number << std::endl;

  return 0;
}
