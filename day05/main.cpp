#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

int main() {
  std::fstream f {"input.txt"};
  std::vector<std::string> lines;
  std::copy(std::istream_iterator<std::string>(f), std::istream_iterator<std::string>(), std::back_inserter(lines));
  std::vector<int> seat_IDs(lines.size(), 0);
  
  for (int line {}; line < lines.size(); ++line) 
    for (auto letter_it {lines[line].begin()}; letter_it != lines[line].end(); ++letter_it) // shifting magic
      seat_IDs[line] += (*letter_it == 'B' || *letter_it == 'R') << (std::distance(letter_it, lines[line].end()) - 1);
  
  std::sort(seat_IDs.begin(), seat_IDs.end());
  const int max {seat_IDs.back()}, min {*(seat_IDs.begin())}, sum {std::accumulate(seat_IDs.begin(), seat_IDs.end(), 0)};
  const auto missing = (max - min + 1) * (max + min) / 2 - sum;
  std::cout << "Part one: " << max << std::endl  << "Part two: " << missing << std::endl;
}