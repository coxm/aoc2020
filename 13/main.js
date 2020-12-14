#!/usr/bin/env node
const input = require('fs')
  .readFileSync(
    process.argv[2] || require('path').join(__dirname, 'input.txt'),
    'utf8'
  )
  .trim()
  .split('\n');
const timestamp = +input[0];


const buses = input[1]
  .trim()
  .split(',')
  .map((val, offset) => {
    const id = val === 'x' ? -1 : +val;
    return {
      id,
      wait: (id + (id - timestamp) % id) % id, // Reduce mod id to [0, id).
      remainder: (id + (id - offset) % id) % id,
    };
  })
  .filter(bus => bus.id !== -1);
// console.log('Buses', buses);


const partOne = buses.reduce((agg, bus) => {
  if (bus.wait < agg.minWait) {
    agg.minWait = bus.wait;
    agg.answer = bus.id * bus.wait;
  }
  return agg;
}, {minWait: Infinity, answer: 0});
console.log('Part one:', partOne.answer);


/** Find an inverse of `val`, modulo `divisor. */
const invertModulo = (val, divisor) => {
  if (divisor === 1 || val === 0 || divisor < 1) {
    return 1;
  }

  const origMod = divisor;
  let a = 0;
  let b = 1;

  while (val > 1) {
    const q = (val / divisor) | 0;
    const rem = val % divisor;
    val = divisor;
    divisor = rem;

    [a, b] = [b - q * a, a];
  }

  return (b + origMod) % origMod; // Ensure the result is positive.
};


/**
 * Perform the constructive proof of the Chinese Remainder Theorem.
 *
 * Use the proof algorithm to find a least positive number `x` such that
 * `x = remainders[i] (mod divisors[i])` for each `i`.
 */
const chineseRemainderTheorem = (remainders, divisors) => {
  const product = divisors.reduce((prod, div) => prod * div, 1);
  const partialProducts = divisors.map(div => product / div);
  const inverses = partialProducts.map(
    (pp, i) => invertModulo(pp, divisors[i]));
  return inverses.reduce((sum, inverse, i) =>
    sum + inverse * partialProducts[i] * remainders[i],
    0
  ) % product;
};


const remainders = [];
const divisors = [];
for (const bus of buses) {
  remainders.push(bus.remainder);
  divisors.push(bus.id);
}
console.log('Part two:', chineseRemainderTheorem(remainders, divisors));
