#include "TestSuite.hpp"
#include "Engine.hpp"

TESTSUITE(engine)
{
    TESTCASE(evaluate)
    {
        Position position;

        check_equal((int)evaluate(position), 0);
    }
}
