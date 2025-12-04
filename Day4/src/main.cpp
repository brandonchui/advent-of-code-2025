// STL
#include <cassert>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// HEADER
#include "helpers.h"

// IMPL
#include "helpers.cpp"

// ---
// enum class Direction { Left, Right, Top, Bottom };

// @ == paper
static int is_paper(const char c) {
  if (c == '@')
    return 1;
  return 0;
}
// static bool move(int r, int c, Direction dir) {
//   switch (dir)
//   case dir::Left: {

//   }
//   default:
//     return false;
// }

int main() {
  auto grid = get_lines_from_input("input1.txt");
  int total = 0;

  for (int row = 0; row < grid.size(); row++) {
    for (int col = 0; col < grid[row].size(); col++) {
      int roll_count = 0;

      // left: (-col)
      if (col - 1 >= 0) {
        roll_count += is_paper(grid[row][col - 1]);
      }

      // right: (+col)
      if (col + 1 < grid[row].size()) {
        roll_count += is_paper(grid[row][col + 1]);
      }

      // top: (-row)
      if (row - 1 >= 0) {
        roll_count += is_paper(grid[row - 1][col]);
      }

      // bot: (+row)
      if (row + 1 < grid.size()) {
        roll_count += is_paper(grid[row + 1][col]);
      }

      // COMBINED
      // diag top left: (-col, -row)
      if (col - 1 >= 0 && row - 1 >= 0) {
        roll_count += is_paper(grid[row - 1][col - 1]);
      }

      // diag top right: (+col, -row)
      if (col + 1 < grid[row].size() && row - 1 >= 0) {
        roll_count += is_paper(grid[row - 1][col + 1]);
      }

      // diag bot left: (-col, +row)
      if (col - 1 >= 0 && row + 1 < grid.size()) {
        roll_count += is_paper(grid[row + 1][col - 1]);
      }

      // diag bot right: (+col, +row)
      if (col + 1 < grid[row].size() && row + 1 < grid.size()) {
        roll_count += is_paper(grid[row + 1][col + 1]);
      }

      // fewer than four rolls of paper
      if (is_paper(grid[row][col]) && roll_count < 4) {
        total++;
      }
    }
  }

  printf("%i\n", total);
  return 0;
}
