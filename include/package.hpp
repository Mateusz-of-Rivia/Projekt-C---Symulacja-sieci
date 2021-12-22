//
// Created by turgo on 12/20/2021.
//

#ifndef UNTITLED5_PACKAGE_HPP
#define UNTITLED5_PACKAGE_HPP

#include <set>
#include "types.hpp"

class Package{
public:
    Package() : elementId(giveID()),isOwner(true) {};
    explicit Package(ElementID_t id) : elementId(id), isOwner(true) {addID(id);};
    Package(Package&& aPackage)  noexcept : elementId(std::move(aPackage.elementId)), isOwner(true){aPackage.isOwner = false; };
    Package(Package& aPackage)  noexcept : elementId(aPackage.elementId), isOwner(true){aPackage.isOwner = false;};
    [[nodiscard]] ElementID_t get_id() const{return elementId;};
    Package& operator=(Package&& aPackage) = default;
    ~Package(){if (isOwner){freeID(elementId);} };

private:
    static void freeID(ElementID_t id);
    static ElementID_t giveID();
    static void addID(ElementID_t id);
    ElementID_t elementId;
    bool isOwner;
    inline static std::set<ElementID_t> assigned_IDs;
    inline static std::set<ElementID_t> freed_IDs;

};
#endif //UNTITLED5_PACKAGE_HPP
