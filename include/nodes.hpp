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

enum class NodesType{
    Ramp,
    Worker,
    Storehouse
};
enum class ReceiverType{ // nie jestem pewien czy to jest dobrze
    Worker,
    Storehouse
};

class IPackageReceiver{
public:
    virtual ElementID_t get_id() = 0;
    virtual NodesType get_type() = 0;
    virtual void receive_package(Package&&) = 0;
    virtual ReceiverType get_receiver_type() = 0; // implementacja tej metody będzie w klasie worker oraz storehouse bede wykorzystywał to do sprawdzenia spójności

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

class PackageSender{
public:
    PackageSender(ReceiverPreferences preferences) : receiver_preferences_(std::move(preferences)){};
    PackageSender(PackageSender&& packageSender) : receiver_preferences_(std::move(packageSender.receiver_preferences_)){};
    void send_package();
    std::optional<Package>& get_sending_buffer(){return buffer;};
protected:
    void push_package(Package&& aPackage){ buffer = std::move(aPackage);};
private:
    ReceiverPreferences receiver_preferences_;
    std::optional<Package> buffer;

};

class Storehouse : public IPackageReceiver{
public:
    Storehouse(ElementID_t id, std::unique_ptr<IPackageStockpile> q) : queue(std::move(q)),id(id){};
    void receive_package(Package&& aPackage) override{queue->push(std::move(aPackage));};
    ElementID_t get_id() override{return id;};
    NodesType get_type()override{return NodesType::Storehouse;};
    ReceiverType get_receiver_type()override{return ReceiverType::Storehouse;}; // powyżej mówiona implementacja powinno zwracac odpowiednia etykięte jeszcze nie wiem co to dokładnie znaczy

    typename IPackageStockpile::const_iterator cbegin()const override{return queue->cbegin();};
    typename IPackageStockpile::const_iterator begin()const override{return queue->cbegin();};
    typename IPackageStockpile::const_iterator cend()const override{return queue->cend();};
    typename IPackageStockpile::const_iterator end()const override{return queue->cend();};
private:
    std::unique_ptr<IPackageStockpile> queue;
    ElementID_t id;
};

class Worker : public PackageSender, public IPackageReceiver {
public:
    Worker(ReceiverPreferences preferences, ElementID_t id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : PackageSender(std::move(preferences)),queue(std::move(q)), id(id), pd(pd){};
    Worker(Worker&& worker): PackageSender(std::move(worker)){Worker(std::move(worker));};
    void receive_package(Package&& aPackage) override{queue->push(std::move(aPackage));};
    void do_work(Time t);
    [[nodiscard]] TimeOffset get_processing_duration() const{return pd;};
    [[nodiscard]] Time get_package_processing_start_time() const{return package_processing_start_time;};
    ElementID_t get_id() override{return id;};
    NodesType get_type()override{return NodesType::Worker;};
    ReceiverType get_receiver_type()override{return ReceiverType::Worker;}; // powyżej mówiona implementacja powinno zwracac odpowiednia etykięte jeszcze nie wiem co to dokładnie znaczy

    typename IPackageStockpile::const_iterator cbegin()const override{return queue->cbegin();};
    typename IPackageStockpile::const_iterator begin()const override{return queue->cbegin();};
    typename IPackageStockpile::const_iterator cend()const override{return queue->cend();};
    typename IPackageStockpile::const_iterator end()const override{return queue->cend();};
private:
    std::unique_ptr<IPackageQueue> queue;
    ElementID_t id;
    TimeOffset pd;
    Time package_processing_start_time;
    std::optional<Package> actual_package;
};

class Ramp : public PackageSender {
public:
    Ramp(ReceiverPreferences preferences, ElementID_t id, TimeOffset di) : PackageSender(std::move(preferences)), id(id), di(di) {};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval(){return di;};
    ElementID_t get_id(){return id;};
    NodesType get_type(){return NodesType::Ramp;};

private:
    ElementID_t id;
    TimeOffset di;
};
#endif //MAIN_CPP_NODES_HPP
