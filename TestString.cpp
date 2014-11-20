#include "TestSuite.hpp"
#include "String.hpp"

TEST(itostr_unsigned_int)
{
    check_equal(itostr(1u), std::string("1"));
    check_equal(itostr(10u), std::string("10"));
    check_equal(itostr(101u), std::string("101"));
    check_equal(itostr(12345u), std::string("12345"));
}


TEST(itostr_signed_int)
{
    check_equal(itostr(1), std::string("1"));
    check_equal(itostr(10), std::string("10"));
    check_equal(itostr(101), std::string("101"));
    check_equal(itostr(12345), std::string("12345"));
    check_equal(itostr(-1), std::string("-1"));
    check_equal(itostr(-10), std::string("-10"));
    check_equal(itostr(-101), std::string("-101"));
    check_equal(itostr(-12345), std::string("-12345"));
}


TESTMAIN()
