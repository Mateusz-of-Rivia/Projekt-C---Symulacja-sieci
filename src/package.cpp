//
// Created by turgo on 12/20/2021.
//
#include "package.hpp"

ElementID_t Package::giveID(){
    if(!freed_IDs.empty()){
        auto iterator = freed_IDs.begin();
        ElementID_t id = *iterator;
        freed_IDs.erase(iterator);  //usuwanie z wolnych
        assigned_IDs.insert(id);    //dodanie do użytych
        return id;
    }
    else if (assigned_IDs.empty()){
        ElementID_t id = 1;
        assigned_IDs.insert(id);
        return id;
    }
    else {
        auto iterator = assigned_IDs.end();
        ElementID_t id = *iterator + 1;
        assigned_IDs.insert(id);
        return id;
    }
}
void Package::freeID(ElementID_t id) {
    assigned_IDs.erase(id);
    freed_IDs.insert(id);
}

void Package::addID(ElementID_t id) {
    assigned_IDs.insert(id);
}