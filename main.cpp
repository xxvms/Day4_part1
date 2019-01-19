#include "Guards.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
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

  std::cout << "test\n";

  return 0;
}

/*int extract_from_string(std::forward_iterator_tag GuardID) {

  std::string IDS{};
std::string tmp[{};
int ID = 0;

if (isdigit(*GuardID)) {
    IDS.insert(0, 1, *GuardID);
    tmp.append(IDS);
    IDS = {};
}

if (!tmp.empty()) {                // converting string with ID into INT
    ID = std::stoi(tmp);
    tmp = {};
}
return ID;
}; // function to save extracted data to my data
*/

void read_file_string(std::vector<std::string> &import_file) {
  std::ifstream file("Day4test.txt");
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

void import_data_to_guards(std::vector<std::string> &puzzle,
                           std::vector<std::string> &split_puzzle) {

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

void import_data_to_map(const std::vector<std::string> &input_from_file,
                        std::map<int, std::vector<Guards>> &destination_file) {

  std::vector<Guards> my_guards_timestamps{}; // vector of timestamps
  int ID = 0;
  bool sleep = true;
  int awake = 0;
  int asleep = 0;
  std::stringstream ss;

  for (auto const &line : input_from_file) {

    std::cout << line << '\n';
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
            std::cout << "ID: " << ID << '\n';
            ss.clear();

        } else if (*Asleep and sleep) {

            while (*Asleep != ']') {
                *Asleep++;
                if (isdigit(*Asleep)) {
                    std::cout << "Asl: " << *Asleep << '\n';
                    ss << *Asleep;
                }

            }
            sleep = false;
            ss >> asleep;
            ss.clear();
            std::cout << "Asleep: " << asleep << '\n';


        } else if (*Asleep and !sleep) {

            while (*Asleep != ']') {
                *Asleep++;
                if (isdigit(*Asleep)) {
                    ss << *Asleep;
                }
            }
            ss >> awake;
            ss.clear();
            std::cout << "Awake: " << awake << '\n';
            sleep = true;
        }
    } else if (ID != 0) {
          my_guards_timestamps.emplace_back(ID, asleep, awake);
          ID = 0;
      }
  }
    std::cout << "blach\n";

  destination_file.insert(std::make_pair(ID, my_guards_timestamps));





}
