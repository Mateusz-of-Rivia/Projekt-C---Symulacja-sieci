//
// Created by turgo on 1/4/2022.
//

#ifndef MAIN_CPP_FACTORY_HPP
#define MAIN_CPP_FACTORY_HPP

#include <mmcobj.h>
#include "nodes.hpp"

class NodeCollection<Node>{
    using container_t = typename std_container_t<Node>; // Wydaje mi się że tutaj zamiast std_container musi być ten bufor robiony w packersenderze ale nie jestem pewien
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    void add(Node Node&&){}
    void remove_by_id(ElementID_t id){}
    NodeCollection<Node>::iterator find_by_id(ElementID_t id){};
    NodeCollection<Node>::const_iterator find_by_id(ElementID_t id){};
};

class Factory {
public:// W public stwórz jeszcze takie API które umożliwi wykonanie wszystkich niezbędnych operacji w private
    void add_ramp(Ramp&&);
    void remove_ramp(ElementID_t id){std::move()};// tutaj trzeba użyć funkcji std::move ale nie wiem jak zaimplementować
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID_t id){}; // tutaj w instrukcji pisze że trzeba użyć std::find_if próbowałem ale nie wiem jakie warunki trzeba użyć
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID_t id);
    NodeCollection<Ramp>::const_iterator ramp_cbegin(){}
    NodeCollection<Ramp>::const_iterator ramp_cend(){}
    // tutaj dalej trzeba powtórzyć to co wyżej ale dla klas worker i Storehouse tylko mam problem z implementacją metod

private:
    void remove_receiver(NodeCollection<Node>& collection, ElementID_t id){}
    bool is_consistent(); //sprawdzanie spójności sieci
    void do_deliveries(Time t){Ramp r; r.deliver_goods(t);} //dokonywanie ewentualnych dostaw na rampy
    void do_package_passing(){PackageSender.send_package()} //dokonywanie ewentualnego przekazywania półproduktów
    void do_work(Time t){Worker.do_work(t)} //dokonywanie ewentualnego przetwarzania półproduktów przez robotników

};

#endif //MAIN_CPP_FACTORY_HPP
