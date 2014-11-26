#ifndef AGENT_HPP
#define AGENT_HPP

#include "Position.hpp"

class Agent
{
public:
    virtual Position move(const Position& position, Field& move) = 0;
    virtual ~Agent() { }
};

#endif
