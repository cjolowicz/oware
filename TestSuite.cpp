#include "TestSuite.hpp"
#include "Exception.hpp"

#include <stdio.h>

TestSuite::TestSuite()
    : m_testcases()
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

        fprintf(stdout, "PASS: %s\n", testcase.name().c_str());
    }
    catch (const Exception& exception)
    {
        fprintf(stdout, "FAIL: %s\n", testcase.name().c_str());

        fprintf(stderr, "%s\n", exception.what());
    }
}
