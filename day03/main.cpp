#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
  std::fstream f {"input.txt"};
  std::vector<std::string> lines;
  std::copy(std::istream_iterator<std::string>(f), std::istream_iterator<std::string>(), std::back_inserter(lines));

  std::vector<std::pair<int, int>> slopes = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
  int trees_mul {1};

  for (const auto & slope : slopes) {
    int position {}, count {};
    for (int i = slope.second; i < lines.size(); i += slope.second) {
      position = (position + slope.first) % lines[i].length();
      count += lines[i][position] == '#';
    }
    std::cout << "Slope: " << slope.first << " " << slope.second << " : " << count << std::endl;
    trees_mul *= count;
  }
  std::cout << "Part two: " << trees_mul << std::endl;

  return 0;
}