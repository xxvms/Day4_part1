#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "Guards.h"
#include <map>
void read_file_string(std::vector<std::string> &import_file);
void import_data_to_guards(std::vector<std::string> &puzzle, std::vector<std::string> &split_p);
void import_data_to_map(const std::vector<std::string>& input_from_file, std::map<int, std::vector<Guards>> & destination_file);


int main() {

  std::vector<std::string> puzzle_input;      // containers for initial puzzle input
  std::vector<std::string> split_p{};           // container of split puzzles

  read_file_string(puzzle_input);

  std::map<int, std::vector<Guards> >  set_of_data; // database of my guards and their timestamp

  import_data_to_map(puzzle_input, set_of_data);





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

void import_data_to_map(const std::vector<std::string>& input_from_file, std::map<int, std::vector<Guards>> & destination_file){

  std::vector<Guards>my_guards_timestamps{}; // vector of timestamps
  int ID = 0;
  std::string IDS{};
  std::string tmp{};
  int awake = 0;
  int asleep = 0;

  for (auto const &line : input_from_file){

    std::cout << line << '\n';
    auto GuardID = std::find(std::begin(line), std::end(line), '#');

          if (*GuardID) {
              while (*GuardID != ' ') {

                  *GuardID++;
                  std::cout << *GuardID << '\n';
                  if (isdigit(*GuardID)) {
                      IDS.insert(0, 1, *GuardID);
                      tmp.append(IDS);
                      IDS = {};
                  }
              }
          }
          if(!tmp.empty()) {
              ID = std::stoi(tmp);
              tmp = {};
          }

      if (ID != 0) {
          my_guards_timestamps.emplace_back(ID, asleep, awake);
          ID = 0;
      }
    }


    {
        destination_file.insert(std::make_pair(ID, my_guards_timestamps));
    }
  std::cout << "blach\n";
}
/*
 *            std::string min{};
              std::string falls {"falls"};
              auto result = line.find(falls);
              std::cout << "Result: " << result << '\n';
              if (std::string::npos ==  result){
                  std::cout << "no luck\n";
                  //[1518-11-01 00:05] falls asleep
                 // std::string tmpS = result-4;
                 // std::cout << tmpS << '\n';
                  if (isdigit(tmpS)) {
                      min.insert(0, 1, tmpS);
                      tmpS.append(IDS);
                      min = {};
                  }
                  if(tmpS != "") {
                      ID = std::stoi(tmpS);
                      tmp = {};
                      std::string min{};
}else{
std::cout << "Didn't found awake\n";
}


*/