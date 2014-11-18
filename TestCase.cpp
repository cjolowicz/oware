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

template<>
void TestCase::check_equal(const std::string& a, const std::string& b)
{
    if (!(a == b))
    {
        fail("expected \"" + b + "\", but got \"" + a + "\"");
    }
}
