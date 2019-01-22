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
void import_data_to_vec(const std::vector<std::string> &input_from_file,
                        std::vector<Guards> &destination_file);
void convert_to_map(const std::vector<Guards> &input_from_vector,
                    std::map<int, std::vector<int>> &my_guards_in_Map);
void finding_sleeper(const std::map<int, std::vector<int>> &my_guards_in_Map,
                     std::map<int, std::vector<int>> &sleeper);
void finding_minute(const std::map<int, std::vector<int>> &find_minute);

int main() {

  std::vector<std::string> puzzle_input; // containers for initial puzzle input
  std::vector<Guards> set_of_data; // database of my guards and their timestamp
  std::map<int, std::vector<int>>
      file_with_g; // lets see if I can keep here map of my guards and their
                   // times awake & asleep
  std::map<int, std::vector<int>>
      sleeping_beauty; // file I will use to bring my sleeping beauty back to
                       // main();

  read_file_string(puzzle_input);

  import_data_to_vec(puzzle_input, set_of_data);

  convert_to_map(set_of_data, file_with_g);

  finding_sleeper(file_with_g, sleeping_beauty);

  finding_minute(sleeping_beauty);

  std::cout << "End of main\n";

  return 0;
}
void finding_minute(const std::map<int, std::vector<int>> &find_minute) {

  std::vector<int> move_to_vec{}; //(60, 0);
  std::vector<int> matrix(60,0);

  for (auto a : find_minute) {
    for (auto aa : a.second) {
      move_to_vec.push_back(aa);
    }
  }

    try {

        for (int j = 0; j < move_to_vec.size(); j+=2) {

            int& I = move_to_vec.at(j);
            int& J = move_to_vec.at(j+1);
            for (int i = I; i <= J ; i++) {

                matrix.at(i)++;
            }
        }
    } catch (const std::out_of_range& e){

        std::cerr << "What is happening: " << e.what();
        throw ;
    }
  std::cout << " test\n";

  std::cout << "End of finding minute\n";
}

void finding_sleeper(const std::map<int, std::vector<int>> &my_guards_in_Map,
                     std::map<int, std::vector<int>> &sleeper) {

  std::map<int, std::vector<int>> tmp;
  int count_tmp = 0;
  for (auto a : my_guards_in_Map) {

    for (size_t i = 0; i < my_guards_in_Map.size(); ++i) {

      count_tmp += a.second.at(i);
    }
    tmp[a.first].push_back(count_tmp);
    count_tmp = 0;
  }

  int winnerMin = 0;
  int winnerID = 0;

  int i = 0;
  try {
    for (auto a : tmp) {
      if (winnerMin < a.second.at(0)) {
        winnerMin = a.second.at(0);
        winnerID = a.first;
        ++i;
      } else {
        ++i;
        continue;
      }
    }
  } catch (const std::out_of_range &e) {
    std::cerr << "Tmp size: " << tmp.size();
    std::cerr << e.what();
    throw;
  }

  std::cout << "*************** Winner is " << winnerID << " with " << winnerMin
            << " minutes of sleep ***************" << '\n';

  sleeper[winnerID] = my_guards_in_Map.at(winnerID);

  std::cout << "End of finding sleeper\n";
} // finding guard that is sleeping most of the time

void convert_to_map(const std::vector<Guards> &input_from_vector,
                    std::map<int, std::vector<int>> &my_guards_in_Map) {

  for (const auto &i : input_from_vector) {

    auto &id =
        i.ID; // thanks Olipro this was an amazing tip to simplify my code :)
    auto &asle = i.asleep;
    auto &awk = i.awake;

    auto tmp = id;

    /* Thanks @bush :)
     *  std::map<int, std::vector<int>> map;
        map[1].push_back(1); // creates a new vector at 1, resulting in {"1":
     [1]} map[1].push_back(2); // uses previous vector at 1, result is {"1": [1,
     2]}
     */

    my_guards_in_Map[id].push_back(asle);
    my_guards_in_Map[id].push_back(awk-1);
  }
  std::cout << "End of conversion to map\n";
} // converting my vector to the map with vector

void read_file_string(std::vector<std::string> &import_file) {
  std::ifstream file("Day4.txt");
  std::string data{};
  if (!file.is_open()) {
    std::cout << "File is not open\n";
  } else {
    while (std::getline(file, data))
      import_file.push_back(data);
    std::cout << "Size of the imported file: " << import_file.size() << '\n';
  }
  std::sort(import_file.begin(), import_file.end());

  std::cout << "End of reading the file\n";

} // changing SOURCE FILE!!!!!!!!

void import_data_to_vec(const std::vector<std::string> &input_from_file,
                        std::vector<Guards> &destination_file) {

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
        destination_file.emplace_back(ID, asleep, awake);
      }
    } else if (ID != 0) {
      std::cout << "Blank for now\n";
    }
  }
  std::cout << "End of importing to vector\n";
} // creating file with my guards and times when they are awake or asleep
