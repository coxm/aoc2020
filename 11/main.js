#!/usr/bin/env node
const FLOOR = 0;
const EMPTY = 1;
const TAKEN = 2;
const FLIP  = TAKEN + EMPTY;


const input = require('fs')
  .readFileSync(
    process.argv[2] || require('path').join(__dirname, 'input.txt'),
    'utf8'
  )
  .trim()
  .split('\n')
  .map(line => [
    FLOOR,
    ...line.split('').map(c => {
      switch (c) {
        case 'L': return EMPTY;
        case '.': return FLOOR;
        case '#': return TAKEN;
        default:
          throw new Error(`Unrecognised character: '${c} ${c.charCodeAt(0)}'`);
      }
    }),
    FLOOR,
  ]);
input.unshift(input[0].map(() => FLOOR));
input.push(input[0]);


const PRINT_MAP = [' ', '!', 'L', '#'];
const print = layout => {
  for (const line of layout) {
    console.log(line.map(v => PRINT_MAP[v]).join(''));
  }
  console.log();
};


const copyInput = () => input.map(line => [...line]);

const directions = [
  // Same eyey.
  [-1,  0],           [ 1,  0],
  // Previous eyey.
  [-1, -1], [ 0, -1], [ 1, -1],
  // Next eyey.
  [-1,  1], [ 0,  1], [ 1,  1],
];


const countOccupied = layout => layout.reduce(
  (total, line) => total + line.reduce(
    (subtotal, value) => subtotal + (value === TAKEN),
    0),
  0);


const advanceSeatPartOne = (seatValue, inLayout, eyex, eyey) => {
  if (seatValue === FLOOR) {
    return FLOOR;
  }
  const occupiedAdjacent = directions.reduce((sum, [x, y]) => {
    return sum + (inLayout[eyey + y][eyex + x] === TAKEN);
  }, 0);
  const changed = seatValue === TAKEN
    ? (occupiedAdjacent >= 4)
    : (occupiedAdjacent === 0);
  return changed ? FLIP - seatValue : seatValue;
};


const look = (layout, eyex, eyey, dx, dy, width, height) => {
  for (
    let x = eyex + dx, y = eyey + dy;
    0 < x && x < width && 0 < y && y < height;
    x += dx, y += dy
  ) {
    const visible = layout[y][x];
    switch (visible) {
      case TAKEN:
        return 1;
      case EMPTY:
        return 0;
      case FLOOR:
        break;
      default:
        throw new Error('Invalid seat');
    }
  }
  return 0;
};


const advanceSeatPartTwo = (
  seatValue, inLayout, eyex, eyey, width, height
) => {
  if (seatValue === FLOOR) {
    return FLOOR;
  }
  let occupiedVisible = directions.reduce(
    (sum, [dx, dy]) => sum + look(inLayout, eyex, eyey, dx, dy, width, height),
    0
  );
  const changed = seatValue === TAKEN
    ? (occupiedVisible >= 5)
    : (occupiedVisible === 0);
  return changed ? FLIP - seatValue : seatValue;
};


const advance = (advanceSeat, inLayout, outLayout) => {
  const height = inLayout.length;
  const width = inLayout[0].length;
  let changeCount = 0;
  for (let r = 0; r < height; ++r) {
    const inRow = inLayout[r];
    const outRow = outLayout[r];
    for (let c = 0; c < width; ++c) {
      const inLayoutValue = inRow[c];
      const outLayoutValue = advanceSeat(
        inLayoutValue, inLayout, c, r, width, height);
      outRow[c] = outLayoutValue;
      changeCount += (inLayoutValue !== outLayoutValue);
    }
  }
  return changeCount;
};


const run = (advanceSeat, limit = Infinity) => {
  let inLayout = copyInput();
  let outLayout = copyInput();
  let i = 0;
  // print(outLayout);
  while (++i < limit && advance(advanceSeat, inLayout, outLayout) !== 0) {
    // print(outLayout);
    [inLayout, outLayout] = [outLayout, inLayout];
  }
  return [countOccupied(outLayout), i];
};


console.log('Part one: %d after %d iterations', ...run(advanceSeatPartOne));
console.log('Part two: %d after %d iterations', ...run(advanceSeatPartTwo));
