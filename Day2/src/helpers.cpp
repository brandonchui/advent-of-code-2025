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
