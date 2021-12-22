//
// Created by turgo on 12/20/2021.
//
#ifndef UNTITLED5_STORAGE_TYPES_HPP
#define UNTITLED5_STORAGE_TYPES_HPP

#include <list>
#include <utility>
#include "package.hpp"
using const_iterator = std::list<Package>::const_iterator;


class IPackageStockpile {
public:
    virtual void push(Package&&) = 0;

    virtual typename std::list<Package>::const_iterator cbegin()const = 0;
    virtual typename std::list<Package>::const_iterator begin()const = 0;
    virtual typename std::list<Package>::const_iterator cend()const = 0;
    virtual typename std::list<Package>::const_iterator end()const = 0;

    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual ~IPackageStockpile() = default;

};

enum class PackageQueueType{
    FIFO,
    LIFO
};


class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};

class PackageQueue : public IPackageQueue{
public:
    explicit PackageQueue(PackageQueueType type, std::list<Package> list = {}) : queue(std::move(list)), queueType(type){};

    typename std::list<Package>::const_iterator cbegin()const override{return queue.cbegin();};
    typename std::list<Package>::const_iterator begin()const override{return queue.cbegin();};
    typename std::list<Package>::const_iterator cend()const override{return queue.cend();};
    typename std::list<Package>::const_iterator end()const override{return queue.cend();};

    size_t size() override{return queue.size();};
    bool empty() override{return queue.empty();};
    void push(Package&& aPackage) override;
    Package pop() override;
    PackageQueueType get_queue_type() override{return queueType;};
private:
    std::list<Package> queue;
    PackageQueueType queueType;
};

#endif //UNTITLED5_STORAGE_TYPES_HPP
