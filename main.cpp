#include "Guards.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
void read_file_string(std::vector<std::string> &import_file);
void import_data_to_guards(std::vector<std::string> &puzzle,
                           std::vector<std::string> &split_p);
void import_data_to_map(const std::vector<std::string> &input_from_file,
                        std::map<int, std::vector<Guards>> &destination_file);

int main() {

  std::vector<std::string> puzzle_input; // containers for initial puzzle input
  std::vector<std::string> split_p{};    // container of split puzzles

  read_file_string(puzzle_input);

  std::map<int, std::vector<Guards>>
      set_of_data; // database of my guards and their timestamp

  import_data_to_map(puzzle_input, set_of_data);

  std::sort(std::begin(set_of_data), std::end(set_of_data));

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


void import_data_to_map(const std::vector<std::string> &input_from_file,
                        std::map<int, std::vector<Guards>> &destination_file) {

  std::vector<Guards> my_guards_timestamps{}; // vector of timestamps
  bool sleep = true;
  int ID = 0;
  std::stringstream ss;
  // std::chrono::minutes awake;
  // std::chrono::minutes asleep;
  int awake = 0;
  int asleep = 0;

  for (auto const &line : input_from_file) {

    auto GuardID = std::find(std::begin(line), std::end(line), '#');
    auto Asleep = std::find(std::begin(line), std::end(line), ':');

    if (*GuardID or *Asleep) {
      if (*GuardID) { // Extracting ID from the line and saving it into tmp
        // string
        while (*GuardID != ' ') {
          *GuardID++;
          if (isdigit(*GuardID)) {
            ss << *GuardID;
          }
        }
        ss >> ID;
        ss.clear();

      } else if (*Asleep and sleep) {

        while (*Asleep != ']') {
          *Asleep++;
          if (isdigit(*Asleep)) {
            ss << *Asleep;
          }
        }
        sleep = false;
        ss >> asleep;
        ss.clear();

      } else if (*Asleep and !sleep) {

        while (*Asleep != ']') {
          *Asleep++;
          if (isdigit(*Asleep)) {
            ss << *Asleep;
          }
        }
        ss >> awake;
        ss.clear();
        sleep = true;
        my_guards_timestamps.emplace_back(ID, asleep, awake);
      }
    } else if (ID != 0) {
    std::cout << "Blank for now\n";
    }
  }

  destination_file.insert(std::make_pair(ID, my_guards_timestamps));
} // creating file with my guards and times when they are awake or asleep


