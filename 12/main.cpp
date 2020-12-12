#include <cmath>
#include <iostream>
#include <fstream>


struct Matrix {
  int a; int b;
  int c; int d;
};


Matrix rotations[4] = {
  { 1,  0,
    0,  1},
  { 0, -1,
    1,  0},
  {-1,  0,
    0, -1},
  { 0,  1,
   -1,  0},
};


struct Point {
  int x;
  int y;

  Point& operator+=(Point a) noexcept {
    x += a.x;
    y += a.y;
    return *this;
  }
};


Point operator*(Matrix const& m, Point const p) noexcept {
  return {m.a * p.x + m.b * p.y, m.c * p.x + m.d * p.y};
}

Point operator*(int scalar, Point const p) noexcept {
  return {scalar * p.x, scalar * p.y};
}


int taxicab(Point const p) noexcept {
  return std::abs(p.x) + std::abs(p.y);
}


int mod4(int v) {
  return (4 + (v % 4)) % 4;
}


struct Rotateable {
  Point location;
  int direction;
};


struct Ship {
  Rotateable one;
  struct PartTwo {
    Rotateable waypoint;
    Point location;
  } two;
};


void north(Ship& ship, int amount) {
  ship.one.location.y += amount;
  ship.two.waypoint.location.y += amount;
}

void east(Ship& ship, int amount) {
  ship.one.location.x += amount;
  ship.two.waypoint.location.x += amount;
}

void south(Ship& ship, int amount) {
  ship.one.location.y -= amount;
  ship.two.waypoint.location.y -= amount;
}

void west(Ship& ship, int amount) {
  ship.one.location.x -= amount;
  ship.two.waypoint.location.x -= amount;
}

void left(Ship& ship, int degrees) {
  int const turns = degrees / 90;
  ship.one.direction += turns;
  auto const& rot = rotations[mod4(turns)];
  ship.two.waypoint.location = rot * ship.two.waypoint.location;
}

void right(Ship& ship, int degrees) {
  left(ship, -degrees);
}

void forward(Ship& ship, int amount) {
  auto const& rot = rotations[mod4(ship.one.direction)];
  ship.one.location += rot * Point{amount, 0};
  ship.two.location += amount * ship.two.waypoint.location;
}


#ifndef NDEBUG
template <typename OS>
OS& operator<<(OS& os, Point p) {
  return os << "{x: " << p.x << ", " << "y: " << p.y << '}';
}


template <typename OS>
OS& operator<<(OS& os, Rotateable const& r) {
  return os << '{' << r.location << ", d: " << r.direction << '}';
}
#endif


int main(int const argc, char const* const* const argv) {
  std::ifstream ifs(argc < 2 ? DEFAULT_INPUT_FILE : argv[1]);

  Ship ship{
    Rotateable{
      Point{0, 0},
      0},
    Ship::PartTwo{
      Rotateable{
        Point{10, 1},
        0},
      Point{0, 0}}};

  for (char action = ifs.get(); ifs.good(); action = ifs.get()) {
    int amount;
    ifs >> amount >> std::ws;
    // Not sure it's worth pre-parsing the input today.
    switch (action) {
      case 'N': north(ship, amount); break;
      case 'S': south(ship, amount); break;
      case 'E': east(ship, amount); break;
      case 'W': west(ship, amount); break;
      case 'L': left(ship, amount); break;
      case 'R': right(ship, amount); break;
      case 'F': forward(ship, amount); break;
      default:
        std::cerr << "Invalid action: " << action << std::endl;
        return 1;
    }

#ifndef NDEBUG
    std::cout << action << ' ' << amount << '\t'
      << ship.two.location << '\t'
      << ship.two.waypoint << std::endl;
#endif
  }

  std::cout << "Part one: " << taxicab(ship.one.location) << '\n'
            << "Part two: " << taxicab(ship.two.location) << std::endl;

  return 0;
}
