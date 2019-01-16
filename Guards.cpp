//
// Created by xxvms on 11/01/19.
//

#include "Guards.h"

//Guards::Guards(){}

//Guards::Guards(int year, int month, int day, int h, int m, int asl, int awa):Year(year), Month(month), Day(day), hour(h), minutes(m), asleep(asl), awake(awa)  {}

Guards::Guards(int id, int asl, int awa): ID(id), asleep(asl), awake(awa){}


Guards& Guards::operator=(Guards other) {
    std::swap(ID, other.ID);
    std::swap(asleep, other.asleep);
    std::swap(awake, other.awake);
}
