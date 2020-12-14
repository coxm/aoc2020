#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>


struct Instruction {
  enum class Type: unsigned char {
    nop = 0,
    acc,
    jmp
  };

  Instruction(
    int value = 0,
    Type type = Type::nop,
    bool executed = false
  )
    : m_value(value)
    , m_type(type)
    , m_executed(executed)
  {
  }

  inline void flip() noexcept {
    m_type = static_cast<Type>(2 - static_cast<unsigned char>(m_type));
  }

  int m_value;
  Type m_type;
  bool m_executed;
};


template <typename InputStream>
InputStream& operator>>(InputStream& input, Instruction& ins) {
  std::string typeStr;
  input >> typeStr;
  if (!input.good()) {
    throw std::invalid_argument("Invalid input");
  }

  Instruction tmp;
  if (typeStr == "acc") {
    tmp.m_type = Instruction::Type::acc;
  }
  else if (typeStr == "jmp") {
    tmp.m_type = Instruction::Type::jmp;
  }
  else if (typeStr == "nop") {
    tmp.m_type = Instruction::Type::nop;
  }
  else {
    throw std::invalid_argument(typeStr);
  }

  input >> tmp.m_value;
  std::swap(ins, tmp);
  return input;
}


constexpr bool INFINITE_LOOP = true;
constexpr bool PROGRAM_TERMINATES = false;


template <typename RAIter>
std::pair<int, bool>
run(RAIter begin, RAIter end) {
  int accumulator = 0;
  for (auto current = begin; current != end; ) {
    if (std::exchange(current->m_executed, true)) {
      return {accumulator, INFINITE_LOOP};
    }
    switch (current->m_type) {
      case Instruction::Type::nop:
        ++current;
        break;
      case Instruction::Type::acc:
        accumulator += current->m_value;
        ++current;
        break;
      case Instruction::Type::jmp:
        current += current->m_value;
        break;
    }
  }
  return {accumulator, PROGRAM_TERMINATES};
}


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  std::vector<Instruction> instructions;
  while (ifs.good() && ifs.peek() != std::ifstream::traits_type::eof()) {
    Instruction ins;
    ifs >> ins >> std::ws;
    instructions.emplace_back(ins);
  }

  auto const partOne = run(
      std::begin(instructions),
      std::end(instructions));

  int partTwo = -1;
  for (auto& ins: instructions) {
    for (auto& instruction: instructions) {
      instruction.m_executed = false;
    }
    ins.flip();
    auto const [accumulator, infinite] = run(
        std::begin(instructions),
        std::end(instructions));
    if (!infinite) {
      partTwo = accumulator;
    }
    ins.flip();
  }

  std::cout << "Part one: " << partOne.first << std::endl;
  std::cout << "Part two: " << partTwo << std::endl;

  return 0;
}
