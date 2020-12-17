#include <vector>
#include <iostream>
#include <map>

int main() {
  std::vector<int> input {7, 14, 0, 17, 11, 1};
  std::map<int, int> last_time_used;
  int last_word = 2;
  int round {0};
  for (const auto & el : input) 
    last_time_used[el] = round++;

  
  for (; round < 30000000 -  1; ++round) {
    if (round == 2020 - 1) 
        std::cout << "Part one: " << last_word << std::endl;

    if (last_time_used.find(last_word) == last_time_used.end()) {
      last_time_used[last_word] = round;
      last_word = 0;
    }
    else {
      int tmp {last_word};
      last_word = round - last_time_used[last_word];
      last_time_used[tmp] = round;
	  }
  }

  std::cout << "Part two: " << last_word << std::endl;
}