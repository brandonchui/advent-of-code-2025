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
