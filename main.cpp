#include "Driver.hpp"

#include <stdlib.h>

int main()
{
    Player human = read_player();

    system("clear");

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
            position = move_agent(position);
        }
    }
    while (!position.is_terminal());

    print(position);

    return 0;
}
