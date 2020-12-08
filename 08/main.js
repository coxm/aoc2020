#!/usr/bin/env node
const regex = /^([a-z]{3}) ([-+]\d+)$/;
const input = require('fs')
  .readFileSync(
    process.argv[2] || require('path').join(__dirname, 'input.txt'),
    'utf8'
  )
  .trim()
  .split('\n')
  .map(line => {
    const match = regex.exec(line);
    if (match === null) {
      throw new Error(`Invalid line: '${line}'`);
    }
    return {
      type: match[1],
      value: +match[2],
      executed: false,
    };
  });


const run = (instructions, reset = true) => {
  let accumulator = 0;
  let index = 0;
  let prevIndex = -1;
  let infinite = false;
  if (reset) {
    for (const ins of instructions) {
      ins.executed = false;
    }
  }
  while (true) {
    const ins = instructions[index];
    if (ins === undefined) {
      break;
    }
    if (ins.executed) {
      infinite = true;
      break;
    }
    ins.executed = true;

    prevIndex = index;
    switch (ins.type) {
      case 'acc':
        accumulator += ins.value;
      case 'nop':
        ++index;
        break;
      case 'jmp':
        index += ins.value;
        break;
      default:
        throw new Error(`Invalid instruction type: '${ins.type}'`);
    }
  }

  return [accumulator, infinite];
};


const partTwo = instructions => {
  for (const ins of instructions) {
    let prevType = ins.type;
    switch (ins.type) {
      case 'acc':
        continue;
      case 'jmp':
        ins.type = 'nop';
        break;
      case 'nop':
        ins.type = 'jmp';
        break;
    }
    const [accumulator, infinite] = run(instructions, true);
    // console.log(
    //   'Swapped %d: %s -> %s: %d (%s)',
    //   i, prevType, ins.type, accumulator, infinite);
    if (!infinite) {
      return accumulator;
    }
    ins.type = prevType;
  }
  return null;
};


module.exports.input = input;
// console.log(input);
console.log('Part one:', run(input, false)[0]);
console.log('Part two:', partTwo(input));
