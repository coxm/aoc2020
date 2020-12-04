#!/usr/bin/env node
const fields = (() => {
  let i = 1;
  return {
    byr: {
      bit: i,
      validate: raw => {
        const year = +raw;
        return 1920 <= year && year <= 2002;
      },
    },
    iyr: {
      bit: i <<= 1,
      validate: raw => {
        const year = +raw;
        return 2010 <= year && year <= 2020;
      },
    },
    eyr: {
      bit: i <<= 1,
      validate: raw => {
        const year = +raw;
        return 2020 <= year && year <= 2030;
      },
    },
    hgt: {
      bit: i <<= 1,
      validate: raw => {
        const cm = raw.endsWith('cm');
        const inches = raw.endsWith('in');
        const value = +raw.substr(0, raw.length - 2);
        return !Number.isNaN(value) && (
          (cm && 150 <= value && value <= 193) ||
          (inches && 59 <= value && value <= 76)
        );
      },
    },
    hcl: {
      bit: i <<= 1,
      validate: raw => /^#[0-9a-f]{6}$/.test(raw),
    },
    ecl: {
      bit: i <<= 1,
      validate: raw =>
        ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'].includes(raw),
    },
    pid: {
      bit: i <<= 1,
      validate: raw => /^[0-9]{9}$/.test(raw)
    },
    cid: {
      bit: i <<= 1,
      validate: raw => true,
    },
  };
})();
module.exports.fields = fields;


const requiredFieldsMask = 255 & ~fields.cid.bit;
module.exports.requiredFieldsMask = requiredFieldsMask;


const entries = require('fs')
  .readFileSync(
    process.argv[2] || require('path').join(__dirname, 'input.txt'),
    'utf8'
  )
  .trim()
  .split('\n\n')
  .map(entry => entry
    .trim()
    .split(/\s+/)
    .reduce((dict, str) => {
      const [key, value] = str.split(':');
      const field = fields[key];
      dict.fields |= fields[key].bit;
      // Node doesn't support &&= :O
      dict.hasRequiredFields =
        (dict.fields & requiredFieldsMask) === requiredFieldsMask;
      const valid = field.validate(value);
      dict.allFieldsValid = dict.allFieldsValid && valid;
      return dict;
    }, {
      fields: 0,
      hasRequiredFields: true,
      allFieldsValid: true,
    }));

// console.log('Entries', entries);
module.exports.entries = entries;

const answers = entries
  .reduce((aggregates, entry) => [
    aggregates[0] + entry.hasRequiredFields,
    aggregates[1] + (entry.hasRequiredFields && entry.allFieldsValid),
  ], [0, 0]);
module.exports.answers = answers;
console.log(...answers);
