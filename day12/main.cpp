#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cmath>

int main() {
  std::fstream f {"input.txt"};
  char c;
  signed long long val, x_pos {}, y_pos {}, x_pos2 {}, y_pos2 {}, direction {1}, waypoint_x {10}, waypoint_y {1};
  std::map<int, char> directions {{0, 'N'}, {1, 'E'}, {2, 'S'}, {3, 'W'}};
  auto move = [&]() {
    if (c == 'N')
      y_pos += val;
    else if (c == 'S')
      y_pos -= val;
    else if (c == 'E')
      x_pos += val;
    else if (c == 'W') 
      x_pos -= val;
  };
  while(f >> c >> val) {
    auto org_x {waypoint_x}, org_y {waypoint_y};
    move();
    if (c == 'N') 
      waypoint_y += val;
    else if (c == 'E')
      waypoint_x += val;
    else if (c == 'S')
      waypoint_y -= val;
    else if (c == 'W') 
      waypoint_x -= val;
    else if (c == 'L') { // Counter clockwise
      direction -= val / 90;
      if (val == 90) {
        waypoint_x = -1 * org_y;
        waypoint_y = org_x;
      } 
      else if (val == 180) {
        waypoint_x = -1 * org_x;
        waypoint_y = -1 * org_y;
      }
      else if (val == 270) {
        waypoint_x = org_y;
        waypoint_y =  -1 * org_x;
      }
    }
    else if (c == 'R') {
      direction += val / 90;
      if (val == 90) {
        waypoint_x = org_y;
        waypoint_y = -1 * org_x;
      } 
      else if (val == 180) {
        waypoint_x = -1 * org_x;
        waypoint_y = -1 * org_y;
      }

      else if (val == 270) {
        waypoint_x = -1 * org_y;
        waypoint_y = org_x;
      }
    }
    if (direction < 0) {
      direction += 4;
    }
    direction = direction % 4;
    if (c == 'F') {
      c = directions[direction];
      move();
      x_pos2 += (waypoint_x * val);
      y_pos2 += (waypoint_y * val);
    }
  }
  std::cout << "Part one: " << std::abs(x_pos) + std::abs(y_pos) << std::endl <<  "Part two: " << std::abs(x_pos2) + std::abs(y_pos2) << std::endl;
} 
             
               