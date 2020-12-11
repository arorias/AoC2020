#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

int main() {
  std::fstream f {"input.txt"};
  std::vector<int> input;
  int i;
  while(f >> i)
    input.push_back(i);

  input.push_back(0);
  std::sort(input.begin(), input.end());
  std::vector<unsigned long long> solution2 (input.back() + 3, 0);
  solution2[0] = 1;
  for (const auto & el : input) {
    if (el - 1 >= 0)
      solution2[el] = solution2[el - 1];
    if (el - 2 >= 0)
      solution2[el] += solution2[el - 2];
    if (el - 3 >= 0)
      solution2[el] += solution2[el - 3];
  }

  std::vector<int> diffs {0, 0, 0, 0};
  input.push_back(input.back() + 3);
  for (int i {1}; i < input.size(); ++i)
    diffs[input[i] - input[i-1]]++;

  std::cout << "Part one: " << (diffs[1] * diffs[3]) << std::endl << "Part two: " << *std::max_element(solution2.begin(), solution2.end()) <<  std::endl;
}
