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

