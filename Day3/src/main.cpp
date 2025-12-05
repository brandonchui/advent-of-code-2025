// STL
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
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
int main(int argc, char *argv[]) {

  auto lines = get_lines_from_input("input.txt");
  long long total = 0;

  for (auto &bank : lines) {
    std::vector<int> vec = vec_string_to_int(bank);

    // change this
    int k = 12;

    int start = 0;
    std::vector<int> digits(k);

    // given array, finds max num given an array range
    // further iters the array size changes for the search
    for (int digit = 0; digit < k; ++digit) {
      int end = vec.size() - (k - digit);
      int curr = start;

      // whats the max num of array on the right side of curr pos
      for (int i = start; i <= end; i++) {
        if (vec[i] > vec[curr])
          curr = i;
      }

      digits[digit] = vec[curr];
      start = curr + 1;
    }

    total += vec_to_big_int(digits);
  }

  printf("%lld\n", total);

  return 0;
}
