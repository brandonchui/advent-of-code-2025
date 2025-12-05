// STL
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

// HEADER
#include "../../utils/helpers.h"

// IMPL
#include "../../utils/helpers.cpp"

//---
struct Range {
  long long start;
  long long end;
};

static Range get_range_from_string(std::string v) {
  long long data[2];
  int i = 0;
  for (auto segment : v | std::views::split('-')) {
    long long converted =
        std::stoll(std::string(segment.begin(), segment.end()));
    data[i] = converted;
    i++;
  }

  return {data[0], data[1]};
}

static long generate(int root) {
  std::string r = std::to_string(root);
  r = r + r;
  return std::stol(r);
}

static bool is_bounded(std::string current_str, std::string limit_str) {
  return !(
      current_str.length() > limit_str.length() ||
      (current_str.length() == limit_str.length() && current_str > limit_str));
}

int main(int argc, char *argv[]) {
  auto lines = get_lines_from_input_delim("input.txt", ',');
  std::vector<Range> ranges{};

  for (const auto &seg : lines) {
    auto range = get_range_from_string(seg);
    ranges.emplace_back(range);
  }
  std::vector<long long> possible_id;
  std::set<long long> unique_ids;

  for (const auto &range : ranges) {
    int root = 1;
    std::string limit_str = std::to_string(range.end);

    while (true) {
      // checks only double like 11, or 2255 etc
      std::string root_str = std::to_string(root);
      std::string current_str = root_str + root_str;

      if (!is_bounded(current_str, limit_str))
        break;

      // checking 1, 11, 111 etc
      while (true) {
        if (!is_bounded(current_str, limit_str))
          break;

        long long val = std::stoll(current_str);

        if (val >= range.start) {
          unique_ids.insert(val);
        }

        current_str += root_str;
      }

      root++;
    }
  }

  long long sum = 0;
  for (const auto &id : unique_ids) {
    sum += id;
  }
  printf("%lld\n", sum);

  return 0;
}
