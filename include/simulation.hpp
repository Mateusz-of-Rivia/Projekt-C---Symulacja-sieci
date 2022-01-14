//
// Created by Asus on 14.01.2022.
//

#ifndef UNTITLED5_SIMULATION_HPP
#define UNTITLED5_SIMULATION_HPP
#include "factory.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)>& rf);

#endif //UNTITLED5_SIMULATION_HPP
