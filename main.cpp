#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "Guards.h"
#include <map>
void read_file_string(std::vector<std::string> &import_file);
void import_data_to_guards(std::vector<std::string> &puzzle, std::vector<std::string> &split_p);

int main() {

  std::vector<std::string> puzzle_input;      // containers for initial puzzle input
  std::vector<std::string> split_p{};           // container of split puzzles

  read_file_string(puzzle_input);



  std::map<int, std::vector<Guards>> set_of_data;
  std::vector<Guards> gs;
  auto a  = Guard_state::start;
  gs.push_back(Guards(1995, 12, 23, 12, 33, a));

  std::cout << "test\n";
  Guard_state state;


  //set_of_data.insert(1, gs.push_back(1995, 12, 23, 12, 33, a));

//    Guards(int year, int month, int day, int h, int m, Guard_state state);

  std::cout << "test\n";

  return 0;
}


void read_file_string(std::vector<std::string> &import_file) {
  std::ifstream file("Day4.txt");
  std::string data{};
  if (!file.is_open()) {
    std::cout << "File is not open\n";
  } else {
    while (std::getline(file, data))
      import_file.push_back(data);
    std::cout << import_file.size() << " <-size\n";
  }
  std::sort(import_file.begin(), import_file.end());

} // changing SOURCE FILE!!!!!!!!

void import_data_to_guards(std::vector<std::string> &puzzle, std::vector<std::string> &split_puzzle) {

  //[1518-11-01 00:00] Guard #10 begins shift

  std::string tmp_string{};
  std::string time_stamp{};
  size_t i = 0;

  for (auto a : puzzle) {

    std::string new_stuff{};

    for (auto b : a) {
      if (i < 17) {
        if (isdigit(b)) {
          tmp_string.insert(0, 1, b);
          time_stamp.append(tmp_string);
          tmp_string = "";
          std::cout << "S: " << time_stamp << '\n';
          i++;
        } else {
          i++;
        }

      } else {
        split_puzzle.push_back(time_stamp);
        i = 0;
        time_stamp = "";
        std::cout << "2nd Else\n";
      }
    }
  }
} // I don't think I will use this