#ifndef TESTSUITE_HPP
#define TESTSUITE_HPP

#include "TestCase.hpp"

#include <vector>

class TestSuite
{
public:
    TestSuite(const std::string& name);

    const std::string& name() const;

    void add(TestCase& testcase);
    int run(int argc, const char* argv[]);

private:
    struct Matcher;

    void runTestCases(const Matcher& match);
    void runTestCase(TestCase& testcase);

    std::string m_name;
    std::vector<TestCase*> m_testcases;
};

#endif
