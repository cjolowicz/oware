#include "Position.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const unsigned int MAX_DEPTH = 9;

void print(const Position& position)
{
    printf("\n");

    Field first;
    Field last;

    first = position.end();
    last = position.begin();

    do
    {
        first.previous();

        printf("%3d", (int)first.index+1);
    }
    while (first != last);

    printf("\n");

    first = position.begin();
    last = position.end();

    while (first != last)
    {
        printf("---");

        first.next();
    }

    printf("---\n");

    first = position.end(PLAYER_A);
    last = position.begin(PLAYER_A);

    do
    {
        first.previous();

        printf("%3d", (int)position.count(first));
    }
    while (first != last);

    printf(" [A] %2d%s\n",
           position.score(PLAYER_A),
           position.player() == PLAYER_A ? " *" : "  ");

    first = position.begin(PLAYER_B);
    last = position.end(PLAYER_B);

    while (first != last)
    {
        printf("%3d", (int)position.count(first));

        first.next();
    }

    printf(" [B] %2d%s\n",
           position.score(PLAYER_B),
           position.player() == PLAYER_B ? " *" : "  ");

    first = position.begin();
    last = position.end();

    while (first != last)
    {
        printf("---");

        first.next();
    }

    printf("---\n");

    first = position.begin();
    last = position.end();

    while (first != last)
    {
        printf("%3d", (int)first.index+1);

        first.next();
    }

    printf("\n");
    printf("\n");
}

void print_move(Field move)
{
    printf("[%s] Move: %d\n",
           move.player == PLAYER_A ? "A" : "B",
           (int)move.index+1);
}

std::pair<Position, bool> read_move(const Position& position)
{
    while (true)
    {
        printf("[%s] Move? ", position.player() == PLAYER_A ? "A" : "B");

        int ch;

        do
        {
            ch = getchar();
        }
        while (isspace(ch));

        switch (ch)
        {
            case '1': return position.move(INDEX_1);
            case '2': return position.move(INDEX_2);
            case '3': return position.move(INDEX_3);
            case '4': return position.move(INDEX_4);
            case '5': return position.move(INDEX_5);
            case '6': return position.move(INDEX_6);
            case EOF:
                printf("\n");
                exit(0);
        }
    }
}

Player read_player()
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
                exit(0);
        }
    }
}

Position move_human(const Position& position)
{
    if (!position.has_move())
    {
        return position.finish();
    }

    std::pair<Position, bool> next;

    while (!next.second)
    {
        next = read_move(position);
    }

    return next.first;
}

Position move_agent(const Position& position)
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
            float value = negamax(next.first, MAX_DEPTH);

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

    print_move(move);

    return best.first;
}

int main()
{
    Player human = read_player();

    Position position;

    do
    {
        print(position);

        if (position.player() == human)
        {
            position = move_human(position);
        }
        else
        {
            position = move_agent(position);
        }
    }
    while (!position.is_terminal());

    print(position);

    return 0;
}
