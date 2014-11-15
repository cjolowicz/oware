#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Position.hpp"

float evaluate(const Position& position);
float negamax(const Position& position, unsigned int depth);

#endif
