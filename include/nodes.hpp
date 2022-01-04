//
// Created by turgo on 12/28/2021.
//

#ifndef MAIN_CPP_NODES_HPP
#define MAIN_CPP_NODES_HPP

#include <memory>
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

/////////////////// Odzielenie działającej części od nie dizłającej xD /////////////////////////////

//////// Piotr Stosik ///////
class PackageSender {
public:
    using receiver_preferences_: ReceiverPreferences;
    PackageSender(PackageSender&&){}
    void send_package(void);
    void get_sending_buffer(void) : std::optional<Package>& {query};
protected:
    void push_package(Package&&);
};

class Storehouse {
public:
    Storehouse(id: ElementID, d: std::unique_ptr<IPackageStockpile>;
};

////// Karol Strojny //////////
class Worker : public PackageSender {
public:
    Worker(ElementID_t id, TimeOffset pd, std::unique_ptr<IPackageQueue> q){}
    void do_work(Time t);
    virtual TimeOffset get_processing_duration() = 0;
    virtual Time get_package_processing_start_time() = 0;


};

class Ramp : public PackageSender {
public:
    ElementID_t id;
    TimeOffset di;
    Ramp(ElementID_t id, TimeOffset di){}
    void deliver_goods(Time t);
    virtual TimeOffset get_delivery_interval() = 0;
    virtual ElementID_t get_id() = 0;
};
















#endif //MAIN_CPP_NODES_HPP
