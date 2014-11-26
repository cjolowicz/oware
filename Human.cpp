#include "Human.hpp"
#include "Engine.hpp"
#include "Debug.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

namespace
{

Field ask_move(Player player)
{
    while (true)
    {
        printf("[%s] Move? ", player == PLAYER_A ? "A" : "B");

        int ch;

        do
        {
            ch = getchar();
        }
        while (isspace(ch));

        switch (ch)
        {
            case '1': return Field(player, INDEX_1);
            case '2': return Field(player, INDEX_2);
            case '3': return Field(player, INDEX_3);
            case '4': return Field(player, INDEX_4);
            case '5': return Field(player, INDEX_5);
            case '6': return Field(player, INDEX_6);
            case EOF:
                throw SystemExit();
        }
    }
}

} // namespace

Position Human::move(const Position& position, Field& move)
{
    if (!position.has_move())
    {
        move = Field();

        return position.finish();
    }

    std::pair<Position, bool> next;

    while (!next.second)
    {
        move = ask_move(position.player());

        next = position.move(move);
    }

    return next.first;
}
