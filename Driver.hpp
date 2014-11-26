#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "Agent.hpp"

#include <string>

enum Mode
{
    HUMAN_VS_HUMAN,
    HUMAN_VS_ENGINE,
    ENGINE_VS_ENGINE
};

Mode toMode(const std::string& rep);

void play(Mode mode);
void play(Agent& a, Agent& b);

#endif
