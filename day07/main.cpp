#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>

unsigned long how_many_bags_contains(std::map<std::string, std::vector<std::pair<int, std::string>>> & bags_included, const std::string & color) {
  unsigned long count {1};
  for (const auto & el : bags_included[color])
    count += el.first * how_many_bags_contains(bags_included, el.second);

  return count;
}

int main() {
  std::fstream f {"input.txt"};
  std::map<std::string, std::vector<std::pair<int, std::string>>> bags_included;
  std::map<std::string, std::set<std::string>> parents;
  std::string line;

  while(std::getline(f, line)) {
    std::stringstream ss {line};
    int no_of_bags;
    std::string token, token2, token3;
    ss >> token >> token2 >> token3 >> token3;
    std::string key {token + token2};
    bags_included[key] = std::vector<std::pair<int, std::string>>();
    while (ss >> no_of_bags >> token >> token2 >> token3) {
      std::string kid {token + token2};
      bags_included[key].push_back(std::make_pair(no_of_bags, kid));
      parents[kid].insert(key);
    }
  }

  std::set<std::string> contains = parents["shinygold"];
  std::queue<std::string> to_check;
  for (const auto & el : contains) to_check.push(el);
  while(!to_check.empty()) {
    for (const auto & parent : parents[to_check.front()]) {
      if (contains.find(parent) == contains.end()) {
        contains.insert(parent);
        to_check.push(parent);
      }
    }
    to_check.pop();
  }
  
  unsigned long bag_count {how_many_bags_contains(bags_included, "shinygold")};
  std::cout << "Part one: " << contains.size() << std::endl << "Part two: " << bag_count - 1 << std::endl;
}