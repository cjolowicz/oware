#include "Test.hpp"
#include "Engine.hpp"

TESTSUITE(engine)
{
    TESTCASE(initial)
    {
        Position position;

        check_close(evaluate(position), 0.0);
    }

    TESTCASE(win)
    {
        Position position(BoardSide(0, 0, 0, 0, 0, 0, 48),
                          BoardSide(0, 0, 0, 0, 0, 0, 0));

        check_close(evaluate(position), 1.0);
    }

    TESTCASE(defeat)
    {
        Position position(BoardSide(0, 0, 0, 0, 0, 0, 0),
                          BoardSide(0, 0, 0, 0, 0, 0, 48));

        check_close(evaluate(position), -1.0);
    }

    TESTCASE(draw)
    {
        Position position(BoardSide(0, 0, 0, 0, 0, 0, 24),
                          BoardSide(0, 0, 0, 0, 0, 0, 24));

        check_close(evaluate(position), 0.0);
    }

    TESTCASE(advantage)
    {
        Position position(BoardSide(4, 4, 4, 4, 4, 4, 2),
                          BoardSide(4, 4, 4, 4, 4, 2, 0));

        check_close(evaluate(position), 0.08);
    }
}
