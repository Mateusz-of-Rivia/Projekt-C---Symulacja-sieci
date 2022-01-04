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

}
void Ramp::deliver_goods(Time t){
    if()
}
///// Piotr Stosik ///////
void send_package(void) {}   //jaka definicja???
void get_sending_buffer(void) : std::optional<Package>& {query} {}   //jaka definicja???
//czy to wszystko?