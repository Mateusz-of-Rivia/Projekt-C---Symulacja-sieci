//
// Created by turgo on 12/28/2021.
//
#include "nodes.hpp"

double ReceiverPreferences::get_propability() {
    if (preferences_.empty()){
        return 1.0;
    }
    else{
        return 1.0 / preferences_.size();
    }
}

void ReceiverPreferences::change_preferences(){     //funkcja zmieniająca wartości prawdopodobieństwa preferences
    for(auto i = preferences_.begin(); i != preferences_.end();i++){
        i->second = get_propability();
    }
}

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    preferences_[receiver] = get_propability();
    change_preferences();
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    preferences_.erase(receiver);
    change_preferences();
}

IPackageReceiver * ReceiverPreferences::choose_receiver() {
    double random = function_();
    if(random == 0){
        return preferences_.cbegin()->first;
    }
    double count1 = 0;
    double count2 = 0;
    for(auto i = preferences_.begin(); i != preferences_.end();i++){
        count2 += i->second;
        if(count1 < random and random <= count2) {
            return i->first;
        }
        count1 = count2;
    }
    return nullptr;
}

/////// Karol Strojny //////
void Worker::do_work(Time t) {
    if(not actual_package.has_value()){         //jeżeli nad niczym nie pracujesz weź z kolejki
        if (not queue->empty()) {
            actual_package = queue->pop();
            package_processing_start_time = t;
        }
    }
    if(t - package_processing_start_time + 1 == pd){            //jeżeli zrobiłeś wsadź do bufora
        push_package(std::move(actual_package.value()));
        actual_package.reset();
    }

}
void Ramp::deliver_goods(Time t){
    if(t % di == 0){                //stwórz produkt i daj do bufora
        Package created_package = Package();
        push_package(std::move(created_package));   //TODO poprawić
    }
}
///// Piotr Stosik ///////
void PackageSender::send_package() {
    IPackageReceiver* receiver_ptr = receiver_preferences_.choose_receiver();  //TODO poprawić
    receiver_ptr->receive_package(std::move(buffer.value()));
    buffer.reset();
}