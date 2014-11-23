#include "Test.hpp"
#include "Engine.hpp"

TESTSUITE(evaluate)
{
    TESTCASE(initial)
    {
        Engine engine;
        Position position;

        check_close(engine.evaluate(position), 0.0);
    }

    TESTCASE(win)
    {
        Engine engine;
        Position position(BoardSide(0, 0, 0, 0, 0, 0, 48),
                          BoardSide(0, 0, 0, 0, 0, 0, 0));

        check_close(engine.evaluate(position), 1.0);
    }

    TESTCASE(defeat)
    {
        Engine engine;
        Position position(BoardSide(0, 0, 0, 0, 0, 0, 0),
                          BoardSide(0, 0, 0, 0, 0, 0, 48));

        check_close(engine.evaluate(position), -1.0);
    }

    TESTCASE(draw)
    {
        Engine engine;
        Position position(BoardSide(0, 0, 0, 0, 0, 0, 24),
                          BoardSide(0, 0, 0, 0, 0, 0, 24));

        check_close(engine.evaluate(position), 0.0);
    }

    TESTCASE(advantage)
    {
        Engine engine;
        Position position(BoardSide(4, 4, 4, 4, 4, 4, 2),
                          BoardSide(4, 4, 4, 4, 4, 2, 0));

        check_close(engine.evaluate(position), 0.08);
    }
}

TESTSUITE(negamax)
{
    TESTCASE(depth_is_zero)
    {
        Engine engine;
        Position position;

        check_close(engine.negamax(position, 0), 0.0);
    }

    TESTCASE(is_terminal)
    {
        Engine engine;
        Position position(BoardSide(0, 0, 0, 0, 0, 0, 48),
                          BoardSide(0, 0, 0, 0, 0, 0, 0));

        check_close(engine.negamax(position), 1.0);
    }

    TESTCASE(finish)
    {
        Engine engine;
        Position position(BoardSide(5, 0, 0, 0, 0, 0, 23),
                          BoardSide(0, 0, 0, 0, 0, 0, 20));

        check_close(engine.negamax(position), 1.0);
    }

    TESTCASE(finish_other)
    {
        Engine engine;
        Position position(BoardSide(0, 0, 0, 0, 0, 5, 23),
                          BoardSide(0, 0, 0, 0, 0, 0, 20));

        check_close(engine.negamax(position), -1.0);
    }

    TESTCASE(1)
    {
        Engine engine;
        Position position(BoardSide(0, 0, 0, 0, 4, 2, 19),
                          BoardSide(1, 1, 0, 0, 0, 0, 21));

        check_close(engine.negamax(position), 1.0);
    }
}
