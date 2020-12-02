#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

constexpr int year {2020};

int main() {
  std::fstream f {"input.txt"};
  int current;
  std::vector<int> input;
  std::map<int, int> diffs;
  std::map<int, std::pair<int, int>> diffs2;
  while(f >> current) {
    input.push_back(current);
    diffs[year - current] = current;
    for (const auto & el : input)
      diffs2[year - el - current] = std::make_pair(el, current);
  }
  
  const auto & it = std::find_if(input.begin(), input.end(), [&](const auto & el) { return diffs.find(el) != diffs.end(); });
  const auto & it2 = std::find_if(input.begin(), input.end(), [&](const auto  &  el) {return diffs2.find(el) != diffs2.end(); });
  
  std::cout << "Part one: " <<  *it *  diffs[*it]  << std::endl
            << "Part two: " << *it2 * diffs2[*it2].first * diffs2[*it2].second 
            << std::endl;
}