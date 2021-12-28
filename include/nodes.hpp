//
// Created by turgo on 12/28/2021.
//

#ifndef MAIN_CPP_NODES_HPP
#define MAIN_CPP_NODES_HPP


#include <functional>
#include <utility>
#include <map>

enum class ReceiverType{
    Ramp,
    Worker,
    Storehouse
};

class IPackageReceiver{
public:
    virtual ElementID_t get_id() = 0;
    virtual ReceiverType get_type() = 0;
    virtual void receive_package(Package&&) = 0;        //TODO nioskonczona klasa
};



class ReceiverPreferences{
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
private:
    preferences_t preferences_;
    std::function<double()> function_;

public:
    ReceiverPreferences(std::function<double()> function, std::map<IPackageReceiver*, double> map) : function_(std::move(function)), preferences_(std::move(map)){};
    double get_propability();
    void change_preferences();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
    choose_receiver
};












#endif //MAIN_CPP_NODES_HPP
