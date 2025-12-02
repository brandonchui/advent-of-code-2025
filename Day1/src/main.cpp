
// STL
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// HEADER
#include "helpers.h"

// IMPL
#include "helpers.cpp"

//---
static void init_dial(std::array<int, 100> &arr) {
  for (uint8_t i = 0; i < 100; ++i)
    arr[i] = i;
}

static int dial_move_left(int &curr, int amount, std::array<int, 100> &arr) {
  if (amount == 0)
    return 0;

  int size = static_cast<int>(arr.size());
  int original = curr;
  curr = ((curr - amount) % size + size) % size;

  if (original == 0)
    return amount / size;
  else
    return (amount >= original) ? 1 + (amount - original) / size : 0;
}

static int dial_move_right(int &curr, int amount, std::array<int, 100> &arr) {
  if (amount == 0)
    return 0;

  int size = static_cast<int>(arr.size());
  int original = curr;
  curr = (curr + amount) % size;

  return (original + amount) / size;
}

struct Rotation {
  const char direction;
  const int amount;
};

static int dial_move(int &curr, Rotation rot, std::array<int, 100> &arr) {
  if (rot.direction == 'L')
    return dial_move_left(curr, rot.amount, arr);
  else
    return dial_move_right(curr, rot.amount, arr);
}

static Rotation extract_rotation_from_string(std::string string) {
  assert(string[0] == 'L' || string[0] == 'R');

  return {string[0], std::stoi(string.substr(1))};
}

int main(int argc, char *argv[]) {
  std::array<int, 100> dial;
  init_dial(dial);

  int current_dial_idx = 50;

  auto v = get_lines_from_input("input.txt");

  int counter = 0;
  for (const auto &line : v) {
    Rotation rot = extract_rotation_from_string(line);
    counter += dial_move(current_dial_idx, rot, dial);
  }

  printf("%i\n", counter);

  return 0;
}
