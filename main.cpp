#include "Driver.hpp"
#include "Engine.hpp"

#include <string>
#include <stdlib.h>

void human_vs_agent(Player human)
{
    system("clear");

    Engine engine;
    Position position;

    do
    {
        if (position.player() != human)
        {
            system("clear");
        }

        print(position);

        if (position.player() == human)
        {
            position = move_human(position);
        }
        else
        {
            position = engine.move(position);
        }
    }
    while (!position.is_terminal());

    print(position);
}

void human_vs_human()
{
    Position position;

    do
    {
        system("clear");

        print(position);

        position = move_human(position);
    }
    while (!position.is_terminal());

    print(position);
}

void agent_vs_agent()
{
    Engine engine;
    Position position;

    do
    {
        print(position);

        position = engine.move(position);
    }
    while (!position.is_terminal());

    print(position);
}

int main(int argc, const char* argv[])
{
    if (argc > 1)
    {
        std::string arg(argv[1]);

        if (arg == "hh")
        {
            human_vs_human();
        }
        else if (arg == "ha" || arg == "ah")
        {
            Player human = read_player();

            human_vs_agent(human);
        }
        else if (arg == "aa")
        {
            agent_vs_agent();
        }
        else
        {
            return 1;
        }
    }
    else
    {
        Player human = read_player();

        human_vs_agent(human);
    }

    return 0;
}
