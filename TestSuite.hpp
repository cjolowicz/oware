#ifndef TESTSUITE_HPP
#define TESTSUITE_HPP

#include "TestCase.hpp"

#include <vector>

class TestSuite
{
public:
    TestSuite(const std::string& name);

    void add(TestCase& testcase);
    int run(int argc, const char* argv[]);

private:
    void runTestCases();
    void runTestCase(TestCase& testcase);

    std::string m_name;
    std::vector<TestCase*> m_testcases;
};

#endif
