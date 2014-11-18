#include "TestSuite.hpp"
#include "String.hpp"

TEST(itostr)
{
    check_equal(itostr(1u), std::string("1"));
}


TESTMAIN()
