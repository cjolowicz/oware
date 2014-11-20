#include "TestSuite.hpp"
#include "Engine.hpp"

TESTSUITE(engine)
{
    TESTCASE(evaluate)
    {
        Position position;

        check_equal(evaluate(position), 0.0);
    }
}
