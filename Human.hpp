#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Agent.hpp"
#include "Exception.hpp"

class Human : public Agent
{
public:
    virtual Position move(const Position& position, Field& move);
};

#endif
