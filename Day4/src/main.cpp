// STL
#include <cassert>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// HEADER
#include "../../utils/helpers.h"

// IMPL
#include "../../utils/helpers.cpp"

// ---
int dirs[8][2] = {
    {0, -1},  // left
    {0, 1},   // right
    {-1, 0},  // top
    {1, 0},   // bottom
    {-1, -1}, // top left
    {-1, 1},  // top right
    {1, -1},  // bottom left
    {1, 1}    // bottom right
};

static int is_paper(const char c) {
  if (c == '@')
    return 1;
  return 0;
}

static int count_adjacent_paper(const std::vector<std::string> &grid, int row,
                                int col) {
  int count = 0;
  for (auto &[dr, dc] : dirs) {
    int nr = row + dr;
    int nc = col + dc;
    if (nr >= 0 && nr < (int)grid.size() && nc >= 0 &&
        nc < (int)grid[nr].size()) {
      count += is_paper(grid[nr][nc]);
    }
  }
  return count;
}

struct Position {
  int row;
  int col;
};

static void remove_rolls(std::vector<std::string> &grid,
                         const std::vector<Position> &pos) {
  for (auto &[row, col] : pos) {
    grid[row][col] = 'x';
  }
}

static int remove_accessible(std::vector<std::string> &grid) {
  std::vector<Position> points;

  for (int row = 0; row < grid.size(); row++) {
    for (int col = 0; col < grid[row].size(); col++) {
      if (is_paper(grid[row][col]) &&
          count_adjacent_paper(grid, row, col) < 4) {
        points.emplace_back(row, col);
      }
    }
  }

  remove_rolls(grid, points);
  return points.size();
}

int main() {
  auto grid = get_lines_from_input("input.txt");
  int total = 0;

  while (int removed = remove_accessible(grid)) {
    total += removed;
  }

  printf("%i\n", total);
  return 0;
}
