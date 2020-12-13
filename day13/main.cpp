#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using ull = unsigned long long;

ull crt(ull base, ull exp, ull modulo) {
  base = base % modulo;
  ull res = {1};
  while (exp > 0) {
      if (exp & 1)  res = (res * base) % modulo;
      base = (base * base) % modulo;
      exp >>= 1;
  }
  return res;
}

int main() {
  // Parsing
  std::fstream f {"input.txt"};
  int leave_time, id;
  std::string line;
  f >> leave_time >> line;
  std::getline(f, line);
  std::vector<int> bus_ids, timestamps, remainders;
  std::istringstream str_buf{line};
  
  for (int ts {}; str_buf >> id; ++ts) {
    bus_ids.push_back(id);
    timestamps.push_back(ts);
    if (( str_buf >> std::ws).peek() == ',') 
      str_buf.ignore();
    while((str_buf >> std::ws).peek() == 'x') {
      str_buf.ignore();
      ++ts;
      while (( str_buf >> std::ws).peek() == ',') 
        str_buf.ignore();
    }
  }

  // Part one
  for (const auto id : bus_ids)
    remainders.emplace_back(std::abs((leave_time / id) * id + id - leave_time));
  const auto min_index = std::distance(remainders.begin(), std::min_element(remainders.begin(), remainders.end()));
  
  // Part two
  ull product {1ULL};
  for (const auto & bus : bus_ids)  product *= bus;
  ull t {};
  for (int i {}; i < bus_ids.size(); ++i) {
    id  = bus_ids[i];
    ull P = product / id;
    t += (id - timestamps[i]) * P * crt(P, id - 2, id);
  }

  std::cout << "Part one: " << bus_ids[min_index] * remainders[min_index] << std::endl << "Part two: " << (t % product) << std::endl;
}