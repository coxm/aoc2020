#!/usr/bin/env node
const seats = require('fs')
  .readFileSync(
    process.argv[2] || require('path').join(__dirname, 'input.txt'),
    'utf8'
  )
  .trim()
  .split(/\s/mg)
  .map(code => parseInt(code.replace(/[FL]/g, '0').replace(/[BR]/g, '1'), 2))
  .sort((a, b) => a - b);
module.exports = seats;


console.log('Part one:', seats[seats.length - 1]);
console.log('Part two:', seats.find((n, i) => n + 1 !== seats[i + 1]) + 1);
