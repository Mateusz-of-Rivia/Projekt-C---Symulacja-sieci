//
// Created by turgo on 12/20/2021.
//
#include "storage_types.hpp"


void PackageQueue::push(Package&& aPackage) {
    switch (QueueType) {
        case PackageQueueType::LIFO:
            queue.push_back(aPackage);
            break;
        case PackageQueueType::FIFO:
            queue.push_front(aPackage);
            break;
    }
}

Package PackageQueue::pop() {
    Package result = queue[-1];
    queue.pop_back();
    return result;
}