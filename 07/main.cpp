#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>


// [fixme] change std::string to std::size_t and use std::hash.
using Stipulation = std::pair<std::string, unsigned>;
using Rule = std::vector<Stipulation>;
using RuleMap = std::unordered_map<std::string, Rule>;


auto
findCount(Rule const& rule, std::string const& type) {
  return std::find_if(
    std::begin(rule),
    std::end(rule),
    [&type] (auto const& pair) {
      return pair.first == type;
    }
  );
}


std::string
readBagType(std::ifstream& input) {
  // Seems most bag names are at most 15 chars, so short string optimisation
  // hopefully means this isn't horribly inefficient.
  std::string adjective;
  std::string colour;
  input >> std::ws >> adjective;
  adjective += input.get();
  input >> colour;
  return adjective + colour;
}


template <typename InputStream>
InputStream&
operator>>(InputStream& input, std::pair<std::string, Rule>& node) {
  // <type>
  std::string ruleType = readBagType(input);

  // "bags contain"
  // constexpr auto offset = std::string(" bags contain ").size();
  constexpr int offset = 14;
  input.seekg(offset, std::ios_base::cur);

  Rule contents;
  char const next = input.peek();
  if ('1' <= next && next <= '9') {
    for (bool moreEntries = input.good(); moreEntries && input.good(); ) {
      // <count>
      unsigned count;
      input >> count >> std::ws;
      // <type>
      std::string type = readBagType(input);
      contents.emplace_back(std::move(type), count);
      input >> type; // bag/bags
      moreEntries = input.peek() != '\n';
    }
  }
  else {
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  }

  std::swap(node.first, ruleType);
  std::swap(node.second, contents);
  return input;
}


void
findAncestors(
  RuleMap const& rules,
  std::unordered_set<std::string>* ancestors,
  std::string const& type
) {
  for (auto const& node: rules) {
    auto const it = findCount(node.second, type);
    if (it != node.second.end()) {
      ancestors->emplace(node.first);
      findAncestors(rules, ancestors, node.first);
    }
  }
}


unsigned
countDescendants(
  RuleMap const& rules,
  std::string const& type,
  unsigned mult = 1
) {
  auto const node = rules.find(type);
  if (node == rules.end()) {
    return 0;
  }

  unsigned sum = 0;
  for (auto const& stipulation: node->second) {
    unsigned const count = stipulation.second;
    unsigned const descendantCount = countDescendants(
      rules, stipulation.first, count);
    sum += mult * (count + descendantCount);
  }
  return sum;
}


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);
  RuleMap rules;
  while (ifs.good() && ifs.peek() != std::fstream::traits_type::eof()) {
    std::pair<std::string, Rule> node;
    ifs >> node;
    rules.emplace(std::move(node));
  }

  std::unordered_set<std::string> ancestors;
  findAncestors(rules, &ancestors, "shiny gold");
  std::cout << "Part one: " << ancestors.size() << std::endl;
  std::cout << "Part two: " << countDescendants(rules, "shiny gold")
    << std::endl;
  return 0;
}
