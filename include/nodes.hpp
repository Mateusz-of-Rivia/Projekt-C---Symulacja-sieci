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
    double get_propability();
    void change_preferences();
public:
    ReceiverPreferences(std::function<double()> function) : function_(std::move(function)){};
    IPackageReceiver* choose_receiver();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
    preferences_t& get_preferences(){return preferences_;};
};












#endif //MAIN_CPP_NODES_HPP
