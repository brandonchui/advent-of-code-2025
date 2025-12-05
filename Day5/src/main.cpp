// STL
#include <cassert>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <string>
#include <vector>

// HEADER
#include "../../utils/helpers.h"

// IMPL
#include "../../utils/helpers.cpp"

using i64 = long long;

struct Range {
  i64 start;
  i64 end;
};

static bool impl_in_range(i64 num, Range range) {
  return (num >= range.start && num <= range.end);
}

static bool in_range(i64 num, std::vector<Range> &range) {
  for (const auto &r : range) {
    if (impl_in_range(num, r))
      return true;
  }
  return false;
}

static Range get_range_from_string(std::string s) {
  std::vector<std::string> data{};
  for (auto segment : s | std::views::split('-')) {
    data.emplace_back(segment.begin(), segment.end());
  }

  assert(data.size() == 2);

  return {std::stoll(data[0]), std::stoll(data[1])};
}

static Range merge(const Range &r1, const Range &r2) {
  i64 s = r1.start < r2.start ? r1.start : r2.start;
  i64 e = r1.end > r2.end ? r1.end : r2.end;

  return {s, e};
};

static bool is_mergable(const Range &r1, const Range &r2) {
  //  1-5, 3-8, 12-15 -> 1-8, 12-15
  // if r1.end is > r2.start AND < r2.end, is mergable
  if (r1.end >= r2.start && r1.end <= r2.end) {
    return true;
  }

  // edge case 1-5 and 5-10
  // edge case 1-10 and 3-5
  if (r1.start <= r2.start && r1.end >= r2.end) {
    return true;
  }

  return false;
}

// ---
int main() {
  auto lines = get_lines_from_input("input.txt");

  ///////////////////////////
  // Part 1
  bool is_reading_ranges = true;

  // get range and food_id from input file and fill it
  std::vector<Range> ranges{};
  std::vector<i64> food_id{};

  for (const auto &line : lines) {
    if (line.empty()) {
      is_reading_ranges = false;
      continue;
    } else if (is_reading_ranges) {
      ranges.emplace_back(get_range_from_string(line));
    } else {
      food_id.emplace_back(std::stoll(line));
    }
  }

  // is the fresh_id within the range vector?
  int total = 0;
  for (const auto &id : food_id) {
    if (in_range(id, ranges))
      total++;
  }

  ///////////////////////////
  // Part 2: all fresh ids from ranges

  // given range 3 - 7, where 3,4,5,6,7 are fresh, total 5
  // 7-3 = 4, + 1 = 5, so range_total = (end-start) + 1
  // --
  // 3-5
  // 10-14
  // 16-20
  // 12-18
  //
  i64 range_total = 0;
  std::vector<Range> merged{};

  // sort ranges
  std::ranges::sort(ranges, [](const Range &r1, const Range &r2) {
    return r1.start < r2.start;
  });

  // merge
  merged.emplace_back(ranges[0]);
  for (int i = 1; i < ranges.size(); ++i) {
    Range &curr = merged.back();
    // merge i with i+1
    // [r1][r2][r3][r4] = last one is ranges[2] merge
    if (is_mergable(curr, ranges[i])) {
      curr = merge(curr, ranges[i]);
    } else {
      merged.emplace_back(ranges[i]);
    }
  }

  // sum
  for (const auto &range : merged) {
    range_total += (range.end - range.start + 1);
  }

  printf("p1: %i\n", total);
  printf("p2: %lld\n", range_total);

  return 0;
}
