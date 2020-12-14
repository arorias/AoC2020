#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using ull = unsigned long long;

ull apply_mask(ull number, std::string mask) {
  ull zeros_mask = (1ULL << 37) - 1;
  ull ones_mask {};
  for (int i {}; i < mask.size(); ++i) 
    if (mask[mask.size() - i - 1] == '1') ones_mask += 1ULL << i;
    else if  (mask[mask.size() - i - 1] == '0') zeros_mask ^= 1ULL << i;
  
  return (number | ones_mask) & zeros_mask;
}

std::vector<ull> apply_mask2(ull address, std::string mask) {
  ull zeros_mask = (1ULL << 37) - 1;
  ull ones_mask {};
  for (int i {}; i < mask.size(); ++i) 
    if (mask[mask.size() - i - 1] == '1') ones_mask += 1ULL << i;
    else if  (mask[mask.size() - i - 1] == 'X') zeros_mask ^= 1ULL << i;

  std::vector<ull> addresses {(address | ones_mask) & zeros_mask};
  for (int i {}; i < mask.size(); ++i) 
    if  (mask[mask.size() - i - 1] == 'X') 
      for (ull j {}, size {addresses.size()}; j < size; ++j)
        addresses.push_back(addresses[j] | (1ULL << i));
    
  return addresses;
}

int main() {
  std::fstream f {"input.txt"};
  std::map<ull, ull> memory, memory2;
  std::string command, eq_string, value, mask;

  while (f >> command >> eq_string >> value) {
    if (command == "mask") 
      mask = value;
    else {
      // Part 1
      const auto address {std::atol(command.substr(4, command.size() - 5).c_str())};
      memory[address] = apply_mask(std::atol(value.c_str()), mask);
      // Part 2
      const auto & addresses = apply_mask2(address, mask);
      for (const auto & ad : addresses)
        memory2[ad] = std::atol(value.c_str());
    }
  }

  auto mem_sum = [](const auto & memory) {
    ull sum {};
    for (const auto & mem : memory)
      sum += mem.second;
    return sum;
  };
 
  std::cout << "Part one: " << mem_sum(memory)  << std::endl << "Part two: " << mem_sum(memory2) << std::endl;
}