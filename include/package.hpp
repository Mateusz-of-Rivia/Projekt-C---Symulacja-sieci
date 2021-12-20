//
// Created by turgo on 12/20/2021.
//

#ifndef UNTITLED5_PACKAGE_HPP
#define UNTITLED5_PACKAGE_HPP

#include "types.hpp"

class Package{
public:
    ElementID_t findID();
    Package() : ElementID(findID()) {};
    explicit Package(ElementID_t id) : ElementID(id) {}
    Package(Package&& aPackage)...???   //TODO Zrobić ten konstruktor
    ElementID_t get_id(){return ElementID;}; //TODO Dorobić metoda operator=
    ~Package()= default;

private:
    ElementID_t ElementID;
    inline static set<ElementID> assigned_IDs;
    inline static set<ElementID> freed_IDs;     //Roboczo założyłem, że freeds_IDs jest posortowana rosnąco.

};
#endif //UNTITLED5_PACKAGE_HPP
