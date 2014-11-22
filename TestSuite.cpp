#include "TestSuite.hpp"
#include "TestRunner.hpp"
#include "Exception.hpp"

#include <stdio.h>

TestSuite::TestSuite(const std::string& name)
    : m_name(name),
      m_testcases()
{
    TestRunner::instance().add(*this);
}

void TestSuite::add(TestCase& testcase)
{
    m_testcases.push_back(&testcase);
}

int TestSuite::run(int argc, const char* argv[])
{
    runTestCases();

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
