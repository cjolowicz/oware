#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Position.hpp"

class Engine
{
public:
    static const unsigned int DEFAULT_DEPTH;

    float negamax(const Position& position, unsigned int depth = DEFAULT_DEPTH);
    float evaluate(const Position& position);
};

#endif
