#include "Driver.hpp"
#include "Human.hpp"
#include "Engine.hpp"
#include "Exception.hpp"

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

namespace
{

Player ask_player()
{
    while (true)
    {
        printf("Player? ");

        int ch;

        do
        {
            ch = getchar();
        }
        while (isspace(ch));

        switch (ch)
        {
            case 'A': case 'a': return PLAYER_A;
            case 'B': case 'b': return PLAYER_B;
            case EOF:
                printf("\n");
                throw SystemExit();
        }
    }
}

void print_position(const Position& position)
{
    fprintf(stdout,
            "   "
            "[ %2d %2d %2d %2d %2d %2d  "
            "| %2d %2d %2d %2d %2d %2d  ] "
            "%2d  - %2d\n",
            (int)position.count(Field(PLAYER_A, INDEX_1)),
            (int)position.count(Field(PLAYER_A, INDEX_2)),
            (int)position.count(Field(PLAYER_A, INDEX_3)),
            (int)position.count(Field(PLAYER_A, INDEX_4)),
            (int)position.count(Field(PLAYER_A, INDEX_5)),
            (int)position.count(Field(PLAYER_A, INDEX_6)),
            (int)position.count(Field(PLAYER_B, INDEX_1)),
            (int)position.count(Field(PLAYER_B, INDEX_2)),
            (int)position.count(Field(PLAYER_B, INDEX_3)),
            (int)position.count(Field(PLAYER_B, INDEX_4)),
            (int)position.count(Field(PLAYER_B, INDEX_5)),
            (int)position.count(Field(PLAYER_B, INDEX_6)),
            (int)position.score(PLAYER_A),
            (int)position.score(PLAYER_B));
}

void print_move(const Position& position, Field move)
{
    fprintf(stdout,
            "%c%d "
            "[ %2d %2d %2d %2d %2d %2d  "
            "| %2d %2d %2d %2d %2d %2d  ] "
            "%2d  - %2d\n",
            move.player == PLAYER_A ? 'A' : 'B',
            (int)move.index+1,
            (int)position.count(Field(PLAYER_A, INDEX_1)),
            (int)position.count(Field(PLAYER_A, INDEX_2)),
            (int)position.count(Field(PLAYER_A, INDEX_3)),
            (int)position.count(Field(PLAYER_A, INDEX_4)),
            (int)position.count(Field(PLAYER_A, INDEX_5)),
            (int)position.count(Field(PLAYER_A, INDEX_6)),
            (int)position.count(Field(PLAYER_B, INDEX_1)),
            (int)position.count(Field(PLAYER_B, INDEX_2)),
            (int)position.count(Field(PLAYER_B, INDEX_3)),
            (int)position.count(Field(PLAYER_B, INDEX_4)),
            (int)position.count(Field(PLAYER_B, INDEX_5)),
            (int)position.count(Field(PLAYER_B, INDEX_6)),
            (int)position.score(PLAYER_A),
            (int)position.score(PLAYER_B));
}

} // namespace

Mode toMode(const std::string& rep)
{
    if (rep == "hh")
    {
        return HUMAN_VS_HUMAN;
    }
    else if (rep == "ha" || rep == "ah")
    {
        return HUMAN_VS_ENGINE;
    }
    else if (rep == "aa")
    {
        return ENGINE_VS_ENGINE;
    }
    else
    {
        throw Exception("invalid argument ", FILELINE);
    }
}

void play(Mode mode)
{
    switch (mode)
    {
        case HUMAN_VS_HUMAN:
            {
                Human human;
                play(human, human);
            }
            break;

        case HUMAN_VS_ENGINE:
            {
                Human human;
                Engine engine;

                if (ask_player() == PLAYER_A)
                {
                    play(human, engine);
                }
                else
                {
                    play(engine, human);
                }
            }
            break;

        case ENGINE_VS_ENGINE:
            {
                Engine engine;
                play(engine, engine);
            }
            break;
    }
}

void play(Agent& a, Agent& b)
{
    Position position;

    print_position(position);

    while (!position.is_terminal())
    {
        Field move;
        position = position.player() == PLAYER_A
            ? a.move(position, move)
            : b.move(position, move);

        print_move(position, move);
    }
}
