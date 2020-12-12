#!/usr/bin/env node
const DIRECTIONS = [
  [ 1,  0], // East.
  [ 0,  1], // North.
  [-1,  0], // West.
  [ 0, -1], // South.
];
DIRECTIONS.E = DIRECTIONS[0];
DIRECTIONS.N = DIRECTIONS[1];
DIRECTIONS.W = DIRECTIONS[2];
DIRECTIONS.S = DIRECTIONS[3];


const mod4 = v => (4 + (v % 4)) % 4;


const ACTIONS_ONE = {
  N(ship, amount) {
    ship.y += amount;
  },
  S(ship, amount) {
    this.N(ship, -amount);
  },
  E(ship, amount) {
    ship.x += amount;
  },
  W(ship, amount) {
    this.E(ship, -amount);
  },
  L(ship, degrees) {
    ship.direction += (degrees / 90);
  },
  R(ship, degrees) {
    this.L(ship, -degrees);
  },
  F(ship, amount, direction) {
    const [dx, dy] = DIRECTIONS[mod4(ship.direction)];
    ship.x += amount * dx;
    ship.y += amount * dy;
  },
};


const ROTATIONS = [
  [ 1,  0,
    0,  1],
  [ 0, -1,
    1,  0],
  [-1,  0,
    0, -1],
  [ 0,  1,
   -1,  0],
].map(rot => new Int32Array(rot));


const ACTIONS_TWO = {
  N(ship, amount) { ACTIONS_ONE.N(ship.wp, amount); },
  S(ship, amount) { ACTIONS_ONE.S(ship.wp, amount); },
  E(ship, amount) { ACTIONS_ONE.E(ship.wp, amount); },
  W(ship, amount) { ACTIONS_ONE.W(ship.wp, amount); },
  L(ship, degrees) {
    const rot = ROTATIONS[mod4(degrees / 90)];
    const x = ship.wp.x;
    const y = ship.wp.y;
    [ship.wp.x, ship.wp.y] = [
      rot[0] * x + rot[1] * y,
      rot[2] * x + rot[3] * y,
    ];
  },
  R(ship, amount) {
    this.L(ship, -amount);
  },
  F(ship, amount) {
    ship.x += amount * ship.wp.x;
    ship.y += amount * ship.wp.y;
  },
};


const ships = require('fs')
  .readFileSync(
    process.argv[2] || require('path').join(__dirname, 'input.txt'),
    'utf8'
  )
  .trim()
  .split('\n')
  .map(s => ({
    action: s[0],
    amount: +s.substr(1),
  }))
  .reduce((ships, {action, amount}) => {
    ACTIONS_ONE[action](ships[0], amount);
    ACTIONS_TWO[action](ships[1], amount);
    // console.debug(action, amount, '\t', ships[1]);
    return ships;
  }, [
    {x: 0, y: 0, direction: 0, wp: undefined},
    {
      x: 0,
      y: 0,
      wp: {x: 10, y: 1, direction: 0},
    },
  ]);
// console.debug(ships);
console.log('Part one:', Math.abs(ships[0].x) + Math.abs(ships[0].y));
console.log('Part two:', Math.abs(ships[1].x) + Math.abs(ships[1].y));
