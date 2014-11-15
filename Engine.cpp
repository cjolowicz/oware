#include "Engine.hpp"

#include <algorithm>
#include <utility>

float evaluate(const Position& position)
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

float negamax(const Position& position, unsigned int depth)
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
