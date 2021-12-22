#include <iostream>
#include "include/package.hpp"
#include "types.hpp"
#include "src/package.cpp"
#include "include/storage_types.hpp"
#include "src/storage_types.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;


    PackageQueue zzz = PackageQueue(PackageQueueType::FIFO);
    zzz.push(Package());
    std::cout << "**** 1" << std::endl << std::flush;
    zzz.push(Package());
    std::cout << "**** 2" << std::endl << std::flush;
    Package p1 = zzz.pop();
    std::cout << "**** 3" << std::endl << std::flush;
    std::cout << p1.get_id() << std::endl << std::flush;
    Package p2 = zzz.pop();
    std::cout << p2.get_id() << std::endl << std::flush;
    return 0;
}
