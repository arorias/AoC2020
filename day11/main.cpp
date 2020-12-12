#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

int occupied_neighbours(const std::vector<std::string> & seats, int x, int y) {
  int sum {};
  for (int i {-1}; i < 2; ++i) {
    for (int j {-1}; j < 2; ++j) {
      if (i == 0 && j == 0)
        continue;
      if (x + i < 0 || y + j < 0)
        continue;
      if (x + i >= seats.size() || y + j >= seats[x].size())
        continue;
      if (seats[x + i][y + j] == '#')
        ++sum;
    }
  }
  return sum;
}

int occupied_neighbours2(const std::vector<std::string> & seats, int x, int y) {
  int sum {};
  for (int i {-1}; i < 2; ++i) {
    for (int j {-1}; j < 2; ++j) {
      if (i == 0 && j == 0)
        continue;
      for (int k {1}; true; ++k) {
        if (x + k * i < 0 || y + k * j < 0)
          break;
        if (x + k * i >= seats.size() || y + k * j >= seats[x].size() || seats[x + k * i][y + k * j] == 'L')
          break;
        if (seats[x + k * i][y + k * j] == '.')
          continue;
        else {
          sum++;
          break;
        }
      }
    }
  }
  return sum;
}

int main() {
  std::fstream f {"input.txt"};
  std::vector<std::string> seats, new_seats, seats2;
  std::string row;
  int result1 {}, result2 {};
  while(std::getline(f, row))
    seats.emplace_back(row);
  seats2 = seats;
  bool state_changed = true;

  while(state_changed) {
    new_seats = seats;
    state_changed = false;
    for (int i {}; i < seats.size(); ++i) 
      for (int j {}; j < seats[i].length(); ++j) 
        if (seats[i][j] != '.') {
          auto n = occupied_neighbours(seats, i, j);
          if ((n == 0) && (seats[i][j] == 'L')) {
            new_seats[i][j] = '#'; 
            state_changed = true;
          }
          else if ((n > 3) && (seats[i][j] == '#')) {
            new_seats[i][j] = 'L'; 
            state_changed = true;
          }
        }
    seats = new_seats;
  }

  state_changed = true;
  while(state_changed) {
    new_seats = seats2;
    state_changed = false;
    for (int i {}; i < seats2.size(); ++i) 
      for (int j {}; j < seats2[i].length(); ++j) 
        if (seats2[i][j] != '.') {
          auto n = occupied_neighbours2(seats2, i, j);
          if ((n == 0) && (seats2[i][j] == 'L')) {
            new_seats[i][j] = '#'; 
            state_changed = true;
          }
          else if ((n > 4) && (seats2[i][j] == '#')) {
            new_seats[i][j] = 'L'; 
            state_changed = true;
          }
        }
    seats2 = new_seats;
  }

  for (const auto & row : seats) 
    result1 += std::count_if(row.begin(), row.end(), [](const auto & c) { return c == '#';});
  for (const auto & row : seats2) 
    result2 += std::count_if(row.begin(), row.end(), [](const auto & c) { return c == '#';});
  
  std::cout << "Part one: " << result1 << std::endl << "Part two: " << result2 << std::endl;
}