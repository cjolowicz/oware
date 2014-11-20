#include "TestSuite.hpp"
#include "Position.hpp"

std::string to_string(Player player)
{
    return player == PLAYER_A ? "A" : "B";
}

std::string to_string(const Position& position, Player player)
{
    std::string result
        = "{ "
        + to_string(player)
        + ", "
        + itostr(position.score(player))
        + ", "
        + "{ ";

    Field first = position.begin(player);
    Field last = position.end(player);

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
        "{ "
        + to_string(position.player())
        + ", "
        + to_string(position, PLAYER_A)
        + ", "
        + to_string(position, PLAYER_B)
        + " }";
}

TESTSUITE(position)
{
    TESTCASE(default)
    {
        Position position;

        check_equal(to_string(position),
                    "{ A"
                    ", { A, 0, { 4, 4, 4, 4, 4, 4 } }"
                    ", { B, 0, { 4, 4, 4, 4, 4, 4 } } }");
    }

    TESTCASE(boardside)
    {
        Position position(BoardSide(0, 1, 2, 3, 4, 5),
                          BoardSide(6, 7, 8, 9, 10, 11));

        check_equal(to_string(position),
                    "{ A"
                    ", { A, 0, { 0, 1, 2, 3, 4, 5 } }"
                    ", { B, 0, { 6, 7, 8, 9, 10, 11 } } }");
    }

    TESTCASE(player)
    {
        Position position(Board(), PLAYER_B);

        check_equal(to_string(position),
                    "{ B"
                    ", { A, 0, { 4, 4, 4, 4, 4, 4 } }"
                    ", { B, 0, { 4, 4, 4, 4, 4, 4 } } }");
    }
}
