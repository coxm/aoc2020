#!/usr/bin/env node
const typeRegex = /^(.*) bags contain (.*)$/;
const contentsRegex = /(\d+) ([^,]+) bags?(, )?/g;


const rules = require('fs')
  .readFileSync(
    process.argv[2] || require('path').join(__dirname, 'input.txt'),
    'utf8'
  )
  .trim()
  .split('\n')
  .map(rule => {
    const typeMatch = typeRegex.exec(rule);
    const type = typeMatch[1];
    const contentsStr = typeMatch[2];
    const contents = {};
    if (typeMatch[2] !== 'no other bags.') {
      let contentsMatch = contentsRegex.exec(contentsStr);
      do {
        contents[contentsMatch[2]] = +contentsMatch[1];
      } while ((contentsMatch = contentsRegex.exec(contentsStr)) !== null);
    }
    return {rule, type, contentsStr, contents};
  });

const ruleMap = rules
  .reduce((dict, node) => {
    (dict[node.type] || (dict[node.type] = [])).push(node);
    return dict;
  }, {});

const findAncestors = (type, ancestors = new Set()) => {
  const parents = rules.filter(rule => rule.contents[type] > 0);
  for (const parent of parents) {
    if (!ancestors.has(parent)) {
      ancestors.add(parent);
      findAncestors(parent.type, ancestors);
    }
  }
  return ancestors;
};

const countDescendants = (type, mult = 1) => {
  let sum = 0;
  const rules = ruleMap[type];
  for (const rule of rules) {
    for (const childType in rule.contents) {
      const count = rule.contents[childType];
      sum += mult * (
        count + countDescendants(childType, rule.contents[childType])
      );
    }
  }
  return sum;
};


console.log(
  'Part one:', findAncestors('shiny gold').size,
  '\nPart two:', countDescendants('shiny gold'),
);
module.exports = rules;
module.exports.findAncestors = findAncestors;
module.exports.countDescendants = countDescendants;
module.exports.ruleMap = ruleMap;
