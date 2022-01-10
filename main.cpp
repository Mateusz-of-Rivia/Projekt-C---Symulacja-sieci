#include <iostream>
#include "include/package.hpp"
#include "types.hpp"
#include "src/package.cpp"
#include "include/storage_types.hpp"
#include "src/storage_types.cpp"
#include "include/nodes.hpp"
#include "src/nodes.cpp"
#include "include/helpers.hpp"
#include "src/helpers.cpp"
int main() {
    std::cout << "Hello, World!" << std::endl;


    ReceiverPreferences ugagu = ReceiverPreferences(probability_generator);
    Ramp r1 = Ramp(ugagu,1,2);
    PackageQueue q = PackageQueue(PackageQueueType::LIFO);
    //std::unique_ptr<IPackageQueue>qq(q);
    //Worker w1 = Worker(ugagu,1,2,std::move(qq));
    //ugagu.add_receiver(w1);
    return 0;
}
