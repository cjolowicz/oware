#include "TestRunner.hpp"

void TestRunner::add(TestSuite& testsuite)
{
    m_testsuites.push_back(&testsuite);
}

int TestRunner::run(int argc, const char* argv[])
{
    int status = 0;

    std::vector<TestSuite*>::iterator testsuite;

    for (testsuite = m_testsuites.begin();
         testsuite != m_testsuites.end(); ++testsuite)
    {
        status |= (**testsuite).run(argc, argv);
    }

    return status;
}

int main(int argc, const char* argv[])
{
    return TestRunner::instance().run(argc, argv);
}
