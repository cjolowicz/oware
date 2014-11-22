#include "TestSuite.hpp"
#include "TestRunner.hpp"
#include "Exception.hpp"

#include <algorithm>

#include <stdio.h>

struct TestSuite::Matcher
{
    Matcher(int argc, const char* argv[])
        : args(&argv[1], &argv[argc])
    {
    }

    bool operator()(const std::string& name) const
    {
        std::vector<std::string>::const_iterator arg;
        for (arg = args.begin(); arg != args.end(); ++arg)
        {
            if (matches(name, *arg))
            {
                return true;
            }
        }

        return args.empty();
    }

    bool matches(const std::string& name, const std::string& arg) const
    {
        return arg.size() <= name.size()
            && std::search(name.begin(), name.end(), arg.begin(), arg.end())
            != name.end();
    }

    std::vector<std::string> args;
};

TestSuite::TestSuite(const std::string& name)
    : m_name(name),
      m_testcases()
{
    TestRunner::instance().add(*this);
}

const std::string& TestSuite::name() const
{
    return m_name;
}

void TestSuite::add(TestCase& testcase)
{
    m_testcases.push_back(&testcase);
}

int TestSuite::run(int argc, const char* argv[])
{
    Matcher match(argc, argv);

    runTestCases(match);

    return 0;
}

void TestSuite::runTestCases(const Matcher& match)
{
    std::vector<TestCase*>::iterator testcase;

    for (testcase = m_testcases.begin();
         testcase != m_testcases.end(); ++testcase)
    {
        std::string fqdn = name() + "." + (**testcase).name();

        if (match(fqdn))
        {
            runTestCase(**testcase);
        }
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
