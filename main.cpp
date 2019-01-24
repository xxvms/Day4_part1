#include "Guards.h"
#include <algorithm>
//#include <chrono>
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

  std::ofstream my_file("Sorted_file.txt");

  for (auto a : import_file) {
    my_file << a << '\n';
  }

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

void convert_to_map(const std::vector<Guards> &input_from_vector,
                    std::map<int, std::vector<int>> &my_guards_in_Map) {

  for (const auto &i : input_from_vector) {
    // thanks Olipro this was an amazing tip to simplify my code :)
    auto &id = i.ID;
    auto &asle = i.asleep;
    auto &awk = i.awake;

    /* Thanks @bush :)
    std::map<int, std::vector<int>> map;
    map[1].push_back(1); // creates a new vector at 1, resulting in {"1": [1]}
    map[1].push_back(2); // uses previous vector at 1, result is {"1": [1,2]}
     */

    my_guards_in_Map[id].push_back(asle);
    my_guards_in_Map[id].push_back(awk-1); // add -1
  }

  std::ofstream my_file("Input_from_vec.txt");

  for (auto a : input_from_vector) {
    my_file << "ID: " << a.ID << '\n';
    my_file << " Asleep: " << a.asleep << '\n';
    my_file << " Awake: " << a.awake << '\n';
  }

  std::cout << "End of conversion to map\n";
} // converting my vector to the map with vector

void finding_sleeper(const std::map<int, std::vector<int>> &my_guards_in_Map,
                     std::map<int, std::vector<int>> &sleeper) {

  std::map<int, std::vector<int>> tmp;
  int count_tmp = 0;
  int count_tmp1 = 0;
  int asleep = 0;
  int awake = 0;

  for (auto a : my_guards_in_Map) {
    int i = 0;
    auto &I = a.second.at(i);

    for (auto b : a.second) {
      if (i % 2 == 0) {
        asleep = b;
        i++;
      } else {
        awake = b;
        count_tmp = awake - asleep;
        count_tmp1 += count_tmp;
        i++;
      }
    }
      tmp[a.first].push_back(count_tmp1);
      count_tmp = 0;
      count_tmp1 = 0;
  }

    int current_winner = 0;
    int current_winner_ID = 0;
    for (auto a : tmp) {

      auto& entry_value = a.second.at(0);

      if (current_winner < entry_value){

          current_winner = entry_value;
          current_winner_ID = a.first;
      } else {
          continue;
      }



  }


  std::cout << "*************** Winner is " << current_winner_ID << " with " << current_winner
            << " minutes of sleep ***************" << '\n';

  sleeper[current_winner_ID] = my_guards_in_Map.at(current_winner_ID);

  std::cout << "End of finding sleeper\n";
} // finding guard that is sleeping most of the time

void finding_minute(const std::map<int, std::vector<int>> &find_minute) {

  std::vector<int> move_to_vec{}; //(60, 0);
  std::vector<int> matrix(60, 0);

  for (auto a : find_minute) {
    for (auto aa : a.second) {
      move_to_vec.push_back(aa);
    }
  }

  for (int j = 0; j < move_to_vec.size(); j += 2) {

    int &I = move_to_vec.at(j);
    int &J = move_to_vec.at(j + 1);
    for (int i = I; i <= J; i++) {

      matrix.at(i)++;
    }
  }

  int highest_min = 0;
  int value_matrix = 0;

  for (size_t i = 0; i < matrix.size(); ++i) {

    auto &I = matrix.at(i);
    if (value_matrix < I) {
      highest_min = i;
      value_matrix = I;

    } else {
      continue;
    }
  }

  std::cout << "********************* Answer is: "
            << highest_min * find_minute.begin()->first
            << " *********************\n";

  std::cout << "End of finding minute\n";
} // finding the answer to the question minute * guardID
