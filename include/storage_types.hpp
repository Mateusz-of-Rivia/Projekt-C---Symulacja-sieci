//
// Created by turgo on 12/20/2021.
//
#ifndef UNTITLED5_STORAGE_TYPES_HPP
#define UNTITLED5_STORAGE_TYPES_HPP

#include "package.hpp"

class IPackageStockpile {
public:
    virtual void push(Package&&){};     //TODO Dodać iteratory
    virtual size_t size(){};
    virtual bool empty(){};
    std::list<Package>::const_iterator{};
    virtual ~IPackageStockpile()= default;

};

enum class PackageQueueType{
    FIFO,
    LIFO
};


class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop(){};
    virtual PackageQueueType get_queue_type(){};
};

class PackageQueue : public IPackageQueue{
public:
    PackageQueue(PackageQueueType type, std::list list = {}) : queue(list), QueueType(type){}; //TODO Poprawić konstruktor
    size_t size() override{return queue.size();};
    bool empty() override{return queue.empty();};
    void push(Package&& aPackage) override;
    Package pop() override;
    PackageQueueType get_queue_type(){return QueueType;};
private:
    std::list queue{};
    PackageQueueType QueueType;
};

#endif //UNTITLED5_STORAGE_TYPES_HPP
