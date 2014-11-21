#include "TestCase.hpp"

TestCase::TestCase(const std::string& name)
    : m_name(name)
{
}

TestCase::~TestCase()
{
}

const std::string& TestCase::name() const
{
    return m_name;
}

void TestCase::fail(const std::string& message)
{
    throw Exception(name() + ": " + message, FILELINE);
}

void TestCase::check_equal(const std::string& a, const std::string& b)
{
    if (!(a == b))
    {
        fail("expected \"" + b + "\", but got \"" + a + "\"");
    }
}

void TestCase::check_equal(int a, int b)
{
    if (!(a == b))
    {
        fail("expected " + itostr(b) + ", but got " + itostr(a));
    }
}

void TestCase::check_equal(unsigned int a, unsigned int b)
{
    if (!(a == b))
    {
        fail("expected " + itostr(b) + ", but got " + itostr(a));
    }
}

void TestCase::check_close(double a, double b, double eta)
{
    if ((a > b ? a - b : b - a) > eta)
    {
        fail("expected " + ftostr(b) + " +- " + ftostr(eta) + ", but got " + ftostr(a));
    }
}
