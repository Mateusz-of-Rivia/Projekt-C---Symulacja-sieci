//
// Created by turgo on 12/20/2021.
//
#include "storage_types.hpp"


void PackageQueue::push(Package&& aPackage) {
    queue.emplace_back(std::move(aPackage));
}

Package PackageQueue::pop() {

    /*
    switch (queueType) {
        case PackageQueueType::LIFO:
            Package& output = queue.back();
            queue.pop_back();
            return output;
            break;
        case PackageQueueType::FIFO:
            Package& output2 = queue.front();
            queue.pop_front();
            return output2;
            break;
        default:
            return Package();
    }*/

    if (queueType == PackageQueueType::LIFO){
        Package output = queue.back();
        queue.pop_back();
        return output;
    }
    else{
        Package output2 = queue.front();
        queue.pop_front();
        return output2;
    }


}