#include "TestSuite.hpp"

void TestSuite::add(TestCase* testcase)
{
    instance().m_testcases.push_back(testcase);
}

int TestSuite::run(int argc, const char* argv[])
{
    try
    {
        instance().runTestCases();
    }
    catch (...)
    {
        return 1;
    }

    return 0;
}

void TestSuite::runTestCases()
{
    std::vector<TestCase*>::iterator testcase;

    for (testcase = m_testcases.begin();
         testcase != m_testcases.end(); ++testcase)
    {
        (**testcase).run();
    }
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
