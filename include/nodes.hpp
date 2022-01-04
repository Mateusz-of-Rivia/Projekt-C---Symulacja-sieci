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
class PackageSender : public ReceiverPreferences {
public:
    ReceiverPreferences receiver_preferences_;

    PackageSender(PackageSender&& packageSender) : receiver_preferences_(std::move(packageSender.receiver_preferences_)){};
    void send_package(Package aPackage){bufor = std::move(aPackage);};        //TODO poprawić, zrobione roboczo
    std::optional<Package>& get_sending_buffer(){return bufor;};
protected:
    void push_package(Package&&);
private:
    std::optional<Package> bufor;
};

class Storehouse {
public:
    Storehouse(id: ElementID, d: std::unique_ptr<IPackageStockpile>;
};

////// Karol Strojny //////////
class Worker : public PackageSender,public IPackageReceiver {
public:
    //Worker(ElementID_t id, TimeOffset pd, std::unique_ptr<IPackageQueue> q){}
    void receive_package(Package&& aPackage) override{queue.push(std::move(aPackage));};
    void do_work(Time t);
    TimeOffset get_processing_duration(){return pd;};
    Time get_package_processing_start_time(){return };
    ElementID_t get_id() override{return id;};
private:
    PackageQueue queue;
    std::optional<Package> actual_package;
    ElementID_t id;
    TimeOffset pd;

};

class Ramp : public PackageSender {
public:
    Ramp(ElementID_t id, TimeOffset di): id(id),di(di){};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval(){return di;};
    ElementID_t get_id(){return id;};

private:
    ElementID_t id;
    TimeOffset di;
};
















#endif //MAIN_CPP_NODES_HPP
