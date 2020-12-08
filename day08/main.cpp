#include <vector>
#include <iostream>
#include <fstream>

struct instruction {
  std::string code;
  int value, times_visited;
  explicit instruction(std::string code, int value) : code {code}, value {value}, times_visited {0} {};
};

std::pair<int, int> execute_code(std::vector<instruction> & instructions) {
  int accu {}, ic {};
  while(ic < instructions.size() && !instructions[ic].times_visited) {
    instructions[ic].times_visited++;
    if (instructions[ic].code == "jmp")
      ic += instructions[ic].value;
    else {
      if (instructions[ic].code == "acc")
         accu += instructions[ic].value;
      ic++;
    }
  }
  return std::make_pair(accu, ic);
}

int main() {
  std::fstream f {"input.txt"};
  std::vector<instruction> instructions;
  std::string code;
  int value;

  while(f >> code >> value) 
    instructions.emplace_back(code, value);

  const auto instructions_copy = instructions;
  auto part1 = execute_code(instructions);
  std::cout << "Part one: " << part1.first << std::endl;

  for (int i {}; i < instructions.size(); ++i) {
    if (instructions[i].times_visited) {
      auto instr_set = instructions_copy;
      if (instructions[i].code != "acc" ) {
        instr_set[i].code = instructions[i].code == "nop" ? "jmp" : "nop";
        const auto res = execute_code(instr_set);
        if (res.second >= instr_set.size()) {
           std::cout << "Part two: " << res.first << std::endl;
           break;
         }
      }
    }
  }
}