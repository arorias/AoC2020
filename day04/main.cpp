#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <regex>

int main() {
  std::fstream f {"input.txt"};
  std::string line;
  std::vector<std::map<std::string, std::string>> passports;
  passports.emplace_back(std::map<std::string, std::string>());

  while(std::getline(f, line)) {
    if (line.length() == 0)
        passports.emplace_back(std::map<std::string, std::string>());
    else  {
      std::string token, token2;
      std::stringstream ss {line};
      while(std::getline(ss, token, ':'))  {
        ss >> token2;
        token = std::regex_replace(token, std::regex("^ +| +$|( ) +"), "$1");
        token2 = std::regex_replace(token2, std::regex("^ +| +$|( ) +"), "$1");
        passports.back()[token] = token2;
      }
    }
  
  }

  std::vector<std::string> passport_fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
  int valid_passports {}, valid_passports2 {};

  for (const auto & passport : passports) {
    int fields_in_passport {};
    for (const auto & field : passport_fields)
     fields_in_passport += passport.find(field) != passport.end();
    
    if (fields_in_passport == passport_fields.size()) {
      valid_passports++;
      int valid_fields {};

      valid_fields += passport.at("pid").length() == 9;
      valid_fields += (std::stoi(passport.at("byr")) >= 1920) &&  (std::stoi(passport.at("byr")) <= 2002);
      valid_fields += (std::stoi(passport.at("iyr")) >= 2010) &&  (std::stoi(passport.at("iyr")) <= 2020);
      valid_fields += (std::stoi(passport.at("eyr")) >= 2020) &&  (std::stoi(passport.at("eyr")) <= 2030);
      std::vector<std::string> valid_eye_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
      valid_fields += std::any_of(valid_eye_colors.begin(), valid_eye_colors.end(), [&](const auto & color) {return color == passport.at("ecl"); });
     
      std::regex re("^#[a-fA-F0-9]{6}$");
      std::cmatch m;
      valid_fields += std::regex_match(passport.at("hcl").c_str(), m, re);

      std::stringstream ss {passport.at("hgt")};
      std::string code;
      int height;
      ss >> height >> code;
      valid_fields += (code == "cm" && height >= 150 && height <= 193) || (code == "in" && height >= 59 && height <= 76);

      if (valid_fields == passport_fields.size())
        valid_passports2++;
    }
  }

  std::cout << "Part one: "  << valid_passports << std::endl;
  std::cout << "Part two: "  << valid_passports2 << std::endl;

  return 0;
}