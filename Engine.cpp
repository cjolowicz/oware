#include "Engine.hpp"
#include "Driver.hpp"
#include "Debug.hpp"

#include <algorithm>
#include <utility>
#include <map>

#define DEBUG_MOVE(position, best, move)                        \
    DEBUG("%c:%d "                                              \
          "[ %2d %2d %2d %2d %2d %2d  "                         \
          "| %2d %2d %2d %2d %2d %2d  ] "                       \
          "[ %2d %2d  ] "                                       \
          "%5g",                                                \
          position.player() == PLAYER_B ? 'A' : 'B',            \
          move,                                                 \
          (int)position.count(Field(PLAYER_A, INDEX_1)),        \
          (int)position.count(Field(PLAYER_A, INDEX_2)),        \
          (int)position.count(Field(PLAYER_A, INDEX_3)),        \
          (int)position.count(Field(PLAYER_A, INDEX_4)),        \
          (int)position.count(Field(PLAYER_A, INDEX_5)),        \
          (int)position.count(Field(PLAYER_A, INDEX_6)),        \
          (int)position.count(Field(PLAYER_B, INDEX_1)),        \
          (int)position.count(Field(PLAYER_B, INDEX_2)),        \
          (int)position.count(Field(PLAYER_B, INDEX_3)),        \
          (int)position.count(Field(PLAYER_B, INDEX_4)),        \
          (int)position.count(Field(PLAYER_B, INDEX_5)),        \
          (int)position.count(Field(PLAYER_B, INDEX_6)),        \
          (int)position.score(PLAYER_A),                        \
          (int)position.score(PLAYER_B),                        \
          (double)best)

const unsigned int Engine::DEFAULT_DEPTH = 9;

Position Engine::move(const Position& position)
{
    Field first = position.begin();
    Field last = position.end();

    std::pair<Position, float> best(position, -1.0);
    Field move;

    while (first != last)
    {
        std::pair<Position, bool> next = position.move(first);

        if (next.second)
        {
            float value = negamax(next.first);

            DEBUG_MOVE(next.first, value, (int)(first.index+1));

            if (value > best.second)
            {
                best.first = next.first;
                best.second = value;

                move = first;
            }
        }

        first.next();
    }

    if (best.second == -1.0)
    {
        return position.finish();
    }

    return best.first;
}

float Engine::evaluate(const Position& position)
{
    float win = 1.0 * position.score() / WIN_COUNT;

    if (win >= 1.0)
    {
        return 1.0;
    }

    float defeat = -1.0 * position.score(position.opponent()) / WIN_COUNT;

    if (defeat <= -1.0)
    {
        return -1.0;
    }

    return win + defeat;
}

float Engine::negamax(const Position& position, unsigned int depth)
{
    if (depth == 0 || position.is_terminal())
    {
        return evaluate(position);
    }

    bool can_move = false;

    float best = -1.0;

    Field first = position.begin();
    Field last = position.end();

    while (first != last)
    {
        std::pair<Position, bool> next = position.move(first);

        if (next.second)
        {
            best = std::max(best, -negamax(next.first, depth-1));

            can_move = true;
        }

        first.next();
    }

    if (!can_move)
    {
        Position next = position.finish();

        return -negamax(next, depth-1);
    }

    return best;
}
