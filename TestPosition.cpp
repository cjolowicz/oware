#include "TestSuite.hpp"
#include "Position.hpp"

std::string to_string(Player player)
{
    return player == PLAYER_A ? "A" : "B";
}

std::string to_string(const Position& position, Player player)
{
    std::string result
        = "{ \""
        + to_string(player)
        + "\", "
        + itostr(position.score(PLAYER_A))
        + ", "
        + "{ ";

    Field first = position.begin(PLAYER_A);
    Field last = position.end(PLAYER_A);

    while (first != last)
    {
        result += itostr(position.count(first));

        first.next();

        if (first != last)
        {
            result += ", ";
        }
    }

    result += " } }";

    return result;
}

std::string to_string(const Position& position)
{
    return
        "{ \""
        + to_string(position.player())
        + "\", "
        + to_string(position, PLAYER_A)
        + ", "
        + to_string(position, PLAYER_B)
        + " }";
}

TEST(ctor)
{
    Position position;

    check_equal(to_string(position),
                "{ \"A\""
                ", { \"A\", 0, { 4, 4, 4, 4, 4, 4 } }"
                ", { \"B\", 0, { 4, 4, 4, 4, 4, 4 } } }");
}

TESTMAIN()
