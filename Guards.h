//
// Created by xxvms on 11/01/19.
//

#ifndef DAY4_PART1_GUARDS_H
#define DAY4_PART1_GUARDS_H

//#include <chrono>
#include <iostream>
#include <algorithm>


class Guards {
public:

    int ID;
    int asleep;
    int awake;


public:
    Guards() = default;
    Guards(int id,int asl, int awa);
    Guards& operator=(Guards other);
    ~Guards() = default;
};




#endif //DAY4_PART1_GUARDS_H
