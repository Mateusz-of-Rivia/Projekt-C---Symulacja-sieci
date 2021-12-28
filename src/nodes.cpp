//
// Created by turgo on 12/28/2021.
//
#include "nodes.hpp"

double ReceiverPreferences::get_propability() {
    if (preferences_.empty()){
        return 1.0
    }
    else{
        return 1.0 / preferences_.size();
    }
}

void ReceiverPreferences::change_preferences(){

}

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver){
    preferences_[receiver] = get_propability();
    change_preferences();
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
    preferences_.erase(receiver);
    change_preferences();
}