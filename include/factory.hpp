//
// Created by turgo on 1/4/2022.
//

#ifndef MAIN_CPP_FACTORY_HPP
#define MAIN_CPP_FACTORY_HPP


#include "types.hpp"
#include "nodes.hpp"
#include <algorithm>
#include "string"
#include <sstream>

template <class Node>
class NodeCollection {
private:
    std::list<Node> node_list;
public:
    using iterator = typename std::list<Node>::iterator;
    using const_iterator = typename std::list<Node>::const_iterator;
    iterator begin() { return node_list.begin(); }
    [[nodiscard]] const_iterator cbegin() const { return node_list.cbegin(); }
    iterator end() { return node_list.end(); }
    [[nodiscard]] const_iterator cend() const { return node_list.cend(); }
    [[nodiscard]] const_iterator begin() const { return node_list.begin(); }
    [[nodiscard]] const_iterator end() const { return node_list.end(); }
    void add(Node& node) { node_list.push_back(std::move(node)); }
    void remove_by_id(ElementID_t id);
    iterator find_by_id(ElementID_t id_);
    [[nodiscard]] const_iterator find_by_id(ElementID_t id_) const;

};

class Factory {
private:
    NodeCollection<Worker> workers_list;
    NodeCollection<Ramp> ramps_list;
    NodeCollection<Storehouse> storehouses_list;
    template <class Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID_t id);
public:
    void add_ramp(Ramp&& r) { ramps_list.add(r); }
    void remove_ramp(ElementID_t id);
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID_t id) { return ramps_list.find_by_id(id); }
    [[nodiscard]] NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID_t id) const { return ramps_list.find_by_id(id); }
    [[nodiscard]] NodeCollection<Ramp>::const_iterator ramp_cbegin() const { return ramps_list.cbegin(); }
    [[nodiscard]] NodeCollection<Ramp>::const_iterator ramp_cend() const { return ramps_list.cend(); }
    [[nodiscard]] NodeCollection<Ramp>::const_iterator ramp_begin() const { return ramps_list.begin(); }
    [[nodiscard]] NodeCollection<Ramp>::const_iterator ramp_end() const { return ramps_list.end(); }
    [[nodiscard]] NodeCollection<Ramp>::iterator ramp_begin()  { return ramps_list.begin(); }
    [[nodiscard]] NodeCollection<Ramp>::iterator ramp_end()  { return ramps_list.end(); }

    void add_worker(Worker&& w) { workers_list.add(w); }
    void remove_worker(ElementID_t id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID_t id) { return workers_list.find_by_id(id); }
    [[nodiscard]] NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID_t id) const { return workers_list.find_by_id(id); }
    [[nodiscard]] NodeCollection<Worker>::const_iterator worker_cbegin() const { return workers_list.cbegin(); }
    [[nodiscard]] NodeCollection<Worker>::const_iterator worker_cend() const { return workers_list.cend(); }
    [[nodiscard]] NodeCollection<Worker>::const_iterator worker_begin() const { return workers_list.begin(); }
    [[nodiscard]] NodeCollection<Worker>::const_iterator worker_end() const { return workers_list.end(); }
    [[nodiscard]] NodeCollection<Worker>::iterator worker_begin() { return workers_list.begin(); }
    [[nodiscard]] NodeCollection<Worker>::iterator worker_end() { return workers_list.end(); }

    void add_storehouse(Storehouse&& s) { storehouses_list.add(s); }
    void remove_storehouse(ElementID_t id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID_t id) { return storehouses_list.find_by_id(id); }
    [[nodiscard]] NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID_t id) const { return storehouses_list.find_by_id(id); }
    [[nodiscard]] NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const { return storehouses_list.cbegin(); }
    [[nodiscard]] NodeCollection<Storehouse>::const_iterator storehouse_cend() const { return storehouses_list.cend(); }
    [[nodiscard]] NodeCollection<Storehouse>::const_iterator storehouse_begin() const { return storehouses_list.begin(); }
    [[nodiscard]] NodeCollection<Storehouse>::const_iterator storehouse_end() const { return storehouses_list.end(); }
    [[nodiscard]] NodeCollection<Storehouse>::iterator storehouse_begin()  { return storehouses_list.begin(); }
    [[nodiscard]] NodeCollection<Storehouse>::iterator storehouse_end()  { return storehouses_list.end(); }

    [[nodiscard]] bool is_consistent() const;
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);
};

class NoReceiversException : public std::logic_error {
public:
    NoReceiversException() : std::logic_error("No receiver") {}
};

template<class Node>
typename NodeCollection<Node>::iterator NodeCollection<Node>::find_by_id(ElementID_t id_) {
    auto it = std::find_if(node_list.begin(), node_list.end(), [id_](const auto& elem){ return (elem.get_id() == id_);});
    return it;
}

template<class Node>
typename NodeCollection<Node>::const_iterator NodeCollection<Node>::find_by_id(ElementID_t id_) const {
    auto it = std::find_if(node_list.cbegin(), node_list.cend(), [id_](const auto& elem){ return (elem.get_id() == id_);});
    return it;
}

template<class Node>
void NodeCollection<Node>::remove_by_id(ElementID_t id) {
    auto it = find_by_id(id);
    if (it != node_list.end()) {
        node_list.erase(it);
    }
}


enum class ElementType{
    LOADING_RAMP, WORKER, STORHOUSE, LINK
};

struct ParsedLineData {
    ElementType element_type;
    std::map<std::string, std::string> parameters;
};

ParsedLineData parse_line(const std::string& line);
Factory load_factory_structure(std::istream& is);
void save_factory_structure(Factory& factory, std::ostream& os);
#endif //MAIN_CPP_FACTORY_HPP
