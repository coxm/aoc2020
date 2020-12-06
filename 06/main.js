#!/usr/bin/env node
console.log(
  require('fs')
  .readFileSync(process.env.INPUT || process.argv[2] || 'input.txt', 'utf8')
  .trim()
  .split('\n\n')
  .map(s => {
    const group = s.split('\n');
    const groupSize = group.length;
    const counts = {};
    for (const person of group) {
      for (const answer of person) {
        counts[answer] = (counts[answer] | 0) + 1;
      }
    }
    let partOne = 0;
    let partTwo = 0;
    for (const question in counts) {
      ++partOne;
      partTwo += (counts[question] === groupSize);
    }
    return [partOne, partTwo];
  })
  .reduce((sums, groupValues) => [
    sums[0] + groupValues[0],
    sums[1] + groupValues[1],
  ], [0, 0])
);
