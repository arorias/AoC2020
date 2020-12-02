#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <algorithm>

int main() {
  std::fstream f {"input.txt"};
  std::string line, pswd;
  int min, max, total {}, total2 {};
  char letter;

  while(std::getline(f, line)) {
    std::stringstream ss {line};
    ss >> min >> letter >> max >> letter >> pswd >> pswd;
    const auto count {std::count(pswd.begin(), pswd.end(), letter)};
    if (count >= min && count <= max)
      total++;
    if (!(pswd[min - 1] == letter) != !(pswd[max - 1] == letter))
      total2++;
  }

  std::cout << "Part 1: " << total << std::endl << "Part 2: " << total2 << std::endl;
  return 0;
}