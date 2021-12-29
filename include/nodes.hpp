//
// Created by turgo on 12/28/2021.
//

#ifndef MAIN_CPP_NODES_HPP
#define MAIN_CPP_NODES_HPP


#include <functional>
#include <utility>
#include <map>
#include "storage_types.hpp"

enum class ReceiverType{
    Ramp,
    Worker,
    Storehouse
};

class IPackageReceiver{
public:
    virtual ElementID_t get_id() = 0;
    virtual ReceiverType get_type() = 0;
    virtual void receive_package(Package&&) = 0;

    virtual typename IPackageStockpile::const_iterator cbegin()const = 0;
    virtual typename IPackageStockpile::const_iterator begin()const = 0;
    virtual typename IPackageStockpile::const_iterator cend()const = 0;
    virtual typename IPackageStockpile::const_iterator end()const = 0;
};



class ReceiverPreferences{
public:
    ReceiverPreferences(std::function<double()> function) : function_(std::move(function)){};
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    typename preferences_t::const_iterator cbegin()const{return preferences_.cbegin();};
    typename preferences_t::const_iterator begin()const{return preferences_.cbegin();};
    typename preferences_t::const_iterator cend()const{return preferences_.cend();};
    typename preferences_t::const_iterator end()const{return preferences_.cend();};

    IPackageReceiver* choose_receiver();
    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
    preferences_t& get_preferences(){return preferences_;};

private:
    preferences_t preferences_;
    std::function<double()> function_;
    double get_propability();
    void change_preferences();
};












#endif //MAIN_CPP_NODES_HPP
