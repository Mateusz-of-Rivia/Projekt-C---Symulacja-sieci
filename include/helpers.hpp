#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include <functional>
#include <random>

#include "types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();
using ProbabilityGenerator = std::function<double()>;
extern ProbabilityGenerator probability_generator;

#endif /* HELPERS_HPP_ */
