#pragma once

std::vector<std::string> get_lines_from_input(const char *path);

std::vector<std::string> get_lines_from_input_delim(const char *path,
                                                    const char delim);

int char_to_int(const char c) { return c - '0'; }

std::vector<int> vec_string_to_int(std::string &s);

long long vec_to_big_int(std::vector<int> v);
