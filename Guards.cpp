//
// Created by xxvms on 11/01/19.
//

#include "Guards.h"

Guards::Guards(int id, int asl, int awa): ID(id), asleep(asl), awake(awa){}


Guards& Guards::operator=(Guards other) {
    std::swap(ID, other.ID);
    std::swap(asleep, other.asleep);
    std::swap(awake, other.awake);
}
