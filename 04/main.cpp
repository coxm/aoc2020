#include <cstdint>
#include <utility>
#include <string>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <iostream>


std::regex const hclRegex("^#[0-9a-f]{6}$");
std::regex const eclRegex("^(amb|blu|brn|gry|grn|hzl|oth)$");
std::regex const pidRegex("^[0-9]{9}$");

bool validateBYR(std::string const& valueStr) {
  auto const year = std::stoul(valueStr);
  return 1920 <= year && year <= 2002;
}

bool validateIYR(std::string const& valueStr) {
  auto const year = std::stoul(valueStr);
  return 2010 <= year && year <= 2020;
}

bool validateEYR(std::string const& valueStr) {
  auto const year = std::stoul(valueStr);
  return 2020 <= year && year <= 2030;
}

bool validateHGT(std::string const& valueStr) {
  std::size_t len = valueStr.size();
  if (len < 2) {
    return false;
  }
  auto const amount = std::stoul(valueStr);
  if (valueStr.ends_with("in")) {
    return 59 <= amount && amount <= 76;
  }
  if (valueStr.ends_with("cm")) {
    return 150 <= amount && amount <= 193;
  }
  return false;
}

bool validateHCL(std::string const& valueStr) {
  return std::regex_search(valueStr, hclRegex);
}

bool validateECL(std::string const& valueStr) {
  return std::regex_search(valueStr, eclRegex);
}

bool validatePID(std::string const& valueStr) {
  return std::regex_search(valueStr, pidRegex);
}

bool validateCID(std::string const& valueStr) {
  return true;
}

bool validateInvalid(std::string const& valueStr) {
  return false;
}


struct Datum {
  static constexpr std::uint8_t s_unknown = 0x00;
  static constexpr std::uint8_t s_byr = 0x01;
  static constexpr std::uint8_t s_iyr = 0x02;
  static constexpr std::uint8_t s_eyr = 0x04;
  static constexpr std::uint8_t s_hgt = 0x08;
  static constexpr std::uint8_t s_hcl = 0x10;
  static constexpr std::uint8_t s_ecl = 0x20;
  static constexpr std::uint8_t s_pid = 0x40;
  static constexpr std::uint8_t s_cid = 0x80;
  static constexpr std::uint8_t s_requiredFields =
    s_byr | s_iyr | s_eyr | s_hgt | s_hcl | s_ecl | s_pid;

  typedef bool(*validator_type)(std::string const&);

  using typeinfo_map_type = 
    std::unordered_map<std::string, std::pair<validator_type, std::uint8_t>>;

  static typeinfo_map_type s_typeInfo;

  static Datum
  parse(std::string const& typeStr, std::string const& valueStr) {
    auto const it = s_typeInfo.find(typeStr);
    if (it == s_typeInfo.end()) {
      std::cout << typeStr << ':' << valueStr << " -> 0:false" << std::endl;
      return {s_unknown, false};
    }

    auto const [validate, type] = it->second;
    bool valid = false;
    try {
      valid = validate(valueStr);
    }
    catch (std::invalid_argument const& err) {
      std::cerr << "Unable to parse (invalid_argument): " << err.what()
        << std::endl;
    }
    catch (std::runtime_error const& err) {
      std::cerr << "Unable to parse (runtime_error): " << err.what()
        << std::endl;
    }

#ifdef VERBOSE
    std::cout << typeStr << ':' << valueStr
      << " -> " << int(type) << ':' << valid
      << std::endl;
#endif
    return {type, valid};
  }

  std::uint8_t m_type;
  bool m_valid;
};


Datum::typeinfo_map_type Datum::s_typeInfo{
  {"byr", {validateBYR, Datum::s_byr}},
  {"iyr", {validateIYR, Datum::s_iyr}},
  {"eyr", {validateEYR, Datum::s_eyr}},
  {"hgt", {validateHGT, Datum::s_hgt}},
  {"hcl", {validateHCL, Datum::s_hcl}},
  {"ecl", {validateECL, Datum::s_ecl}},
  {"pid", {validatePID, Datum::s_pid}},
  {"cid", {validateCID, Datum::s_cid}}
};


template <typename InputStream>
InputStream& operator>>(InputStream& input, Datum& datum) {
  input >> std::ws;
  std::string typeStr;
  std::getline(input, typeStr, ':');
  std::string valueStr;
  input >> valueStr;
  datum = Datum::parse(typeStr, valueStr);
  return input;
}


struct Passport {
  std::uint8_t m_fields;
  bool m_allFieldsValid;

  inline bool hasRequiredFields() const noexcept {
    return (m_fields & Datum::s_requiredFields) == Datum::s_requiredFields;
  }
};


template <typename InputStream>
InputStream& operator>>(InputStream& input, Passport& passport) {
#ifdef VERBOSE
  std::cout << "Passport:\n";
#endif
  Passport tmp{0, true};
  while (!input.eof()) {
    Datum datum;
    input >> datum;
    input.get(); // Consume one space or newline.
    tmp.m_fields |= datum.m_type;
    tmp.m_allFieldsValid &= datum.m_valid;
    char const next = input.peek();
    if (next == '\n' || next == -1) {
      break;
    }
  }
  passport = tmp;
#ifdef VERBOSE
  std::cout << std::hex << int(passport.m_fields) << std::dec
    << ' ' << passport.m_allFieldsValid << "\n" << std::endl;
#endif
  return input;
}


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  unsigned partOne = 0;
  unsigned partTwo = 0;

  while (ifs.good()) {
    Passport passport;
    ifs >> passport;
    bool const hasAllRequiredFields = passport.hasRequiredFields();
    partOne += hasAllRequiredFields;
    partTwo += (hasAllRequiredFields && passport.m_allFieldsValid);
  }

  std::cout << "Part one: " << partOne << "\nPart two: " << partTwo 
    << std::endl;
  return 0;
}
