std::vector<std::string> get_lines_from_input(const char *path) {
  std::vector<std::string> result = {};

  std::ifstream file(path);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      result.emplace_back(std::move(line));
    }
  }

  return result;
}

std::vector<std::string> get_lines_from_input_delim(const char *path,
                                                    const char delim) {

  std::vector<std::string> result;

  std::vector<std::string> raw = get_lines_from_input(path);
  for (auto segment : raw[0] | std::views::split(delim)) {
    result.emplace_back(segment.begin(), segment.end());
  }
  return result;
}

std::vector<int> vec_string_to_int(std::string &s) {
  std::vector<int> res{};
  for (int i = 0; i < s.size(); ++i) {
    res.emplace_back(char_to_int(s[i]));
  }
  return res;
}

long long vec_to_big_int(std::vector<int> v) {
  long long res = 0;
  for (int i = 0; i < v.size(); ++i) {
    res = res * 10 + v[i];
  }

  return res;
}
