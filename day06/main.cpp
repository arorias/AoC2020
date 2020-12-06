#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
  std::fstream f {"input.txt"};
  std::vector<std::set<char>> answers_per_group {std::set<char>()};
  std::vector<std::set<char>> answers_per_group2 {std::set<char>()};
  std::string line;
  bool empty = false; // empty flag - not the best solution but i don't have time today :D

  while(std::getline(f, line)) {
    std::set<char> ans {};
    if (line.length() == 0) {
      answers_per_group.emplace_back(std::set<char>());
      answers_per_group2.emplace_back(std::set<char>());
      empty = false;
    }
    else  {
      for (const char c : line) {
        answers_per_group.back().insert(c);
        if (!empty && (answers_per_group2.back().empty() || (answers_per_group2.back().find(c) != answers_per_group2.back().end())))
          ans.insert(c);
      }
      empty = ans.empty();
      answers_per_group2.back() = ans;
    }
  }


  int sum {}, sum2 {};
  for (const auto & group : answers_per_group)
    sum += group.size();
  for (const auto & group : answers_per_group2)
    sum2 += group.size();
  std::cout << "Part one: " << sum << std::endl << "Part two: " << sum2 << std::endl;
}