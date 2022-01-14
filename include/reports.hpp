//
// Created by Asus on 14.01.2022.
//

#ifndef UNTITLED5_REPORTS_HPP
#define UNTITLED5_REPORTS_HPP
#include "factory.hpp"
#include "nodes.hpp"

class SpecificTurnsReportNotifier {
public:
    SpecificTurnsReportNotifier(std::set<Time> turns): turns(turns){}
    bool should_generate_report(Time t){return turns.count(t) > 0; }
private:
    std::set<Time> turns;

};

class IntervalReportNotifier{
public:
    IntervalReportNotifier(TimeOffset to): to(to){}
    bool should_generate_report(Time t){return (t - 1) % to == 0;}
private:
    TimeOffset to;

};

#endif //UNTITLED5_REPORTS_HPP
