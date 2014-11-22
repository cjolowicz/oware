#ifndef TESTRUNNER_HPP
#define TESTRUNNER_HPP

#include "Singleton.hpp"
#include "TestSuite.hpp"

class TestRunner : public Singleton<TestRunner>
{
public:
    void add(TestSuite& testsuite);
    int run(int argc, const char* argv[]);

private:
    std::vector<TestSuite*> m_testsuites;
};

#endif
