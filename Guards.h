//
// Created by xxvms on 11/01/19.
//

#ifndef DAY4_PART1_GUARDS_H
#define DAY4_PART1_GUARDS_H

#include <chrono>


enum class Guard_state{
    start,
    asleep,
    awake
};

class Guards {
private:

    int Year;
    int Month;
    int Day;
    int hour;
    int minutes;
    Guard_state guard_state;
public:
    Guards(int year, int month, int day, int h, int m, Guard_state i);
    ~Guards();
};




#endif //DAY4_PART1_GUARDS_H
