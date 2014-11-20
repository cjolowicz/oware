#include "TestSuite.hpp"
#include "Exception.hpp"

#include <stdio.h>

TestSuite::TestSuite()
    : m_name(),
      m_testcases()
{
}

TestSuite::~TestSuite()
{
    std::vector<TestCase*>::iterator testcase;

    for (testcase = m_testcases.begin();
         testcase != m_testcases.end(); ++testcase)
    {
        delete *testcase;
    }
}

void TestSuite::setName(const std::string& name)
{
    instance().m_name = name;
}

void TestSuite::add(TestCase* testcase)
{
    instance().m_testcases.push_back(testcase);
}

int TestSuite::run(int argc, const char* argv[])
{
    instance().runTestCases();

    return 0;
}

void TestSuite::runTestCases()
{
    std::vector<TestCase*>::iterator testcase;

    for (testcase = m_testcases.begin();
         testcase != m_testcases.end(); ++testcase)
    {
        runTestCase(**testcase);
    }
}

void TestSuite::runTestCase(TestCase& testcase)
{
    try
    {
        testcase.run();

        fprintf(stdout,
                "PASS: %s.%s\n",
                m_name.c_str(),
                testcase.name().c_str());
    }
    catch (const Exception& exception)
    {
        fprintf(stdout,
                "FAIL: %s.%s\n",
                m_name.c_str(),
                testcase.name().c_str());

        fprintf(stderr, "%s\n", exception.what());
    }
}
