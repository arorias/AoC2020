#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>

int find_not_matching(std::vector<int> & input) {
  bool found {};
  for (int i {25}; i < input.size(); ++i) {
    found = false;
    for (int j {i - 25}; j < input.size(); ++j) {
      for (int k { j + 1}; k < input.size(); ++k) {
        if (input[j] + input[k] == input[i]) {
          found = true;
          continue;
        }
      }
    if (found) continue;
    }
    if (!found) return input[i];
  }
  return 0;
}

int find_matching_set(std::vector<int> & input, int expected_sum) {
  for (int i {}; i < input.size(); ++i) {
    int sum {input[i]};
    for (int j {i +1}; j < input.size(); ++j) {
      sum += input[j];
      if (sum > expected_sum)
        continue;
      else if (sum == expected_sum) {
        auto start {input.begin()};
        std::advance(start, i);
        auto end {input.begin()};
        std::advance(end, j);
        return *std::min_element(start, end) + *std::max_element(start, end);
      }
    }
  }
  return 0;
}

int main() {
  std::fstream f {"input.txt"};
  std::vector<int> input;
  int val;
  while (f >> val)
    input.push_back(val);

  auto result1 = find_not_matching(input);
  std::remove_if(input.begin(), input.end(), [result1](const auto& el) {return el >= result1;});
  auto result2 =  find_matching_set(input, result1);
  std::cout << "Part one: " << result1 <<  std::endl << "Part two: " << result2 << std::endl;
}