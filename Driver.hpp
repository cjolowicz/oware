#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "Position.hpp"

Player read_player();
void print(const Position& position);
Position move_human(const Position& position);
Position move_agent(const Position& position);

#endif
