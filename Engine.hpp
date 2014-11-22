#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Position.hpp"

extern const unsigned int DEFAULT_DEPTH;

float evaluate(const Position& position);
float negamax(const Position& position, unsigned int depth = DEFAULT_DEPTH);

#endif
