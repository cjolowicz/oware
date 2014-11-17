#ifndef TESTSUITE_HPP
#define TESTSUITE_HPP

#include "Singleton.hpp"
#include "TestCase.hpp"

#include <vector>

class TestSuite : public Singleton<TestSuite>
{
public:
    static void add(TestCase* testcase);
    static int run(int argc, const char* argv[]);

    ~TestSuite();

    template<typename T>
    struct Add
    {
        Add()
        {
            add(new T);
        }

        static Add s_add;
    };

private:
    void runTestCases();

    std::vector<TestCase*> m_testcases;
};

template<typename T>
TestSuite::Add<T>
TestSuite::Add<T>::s_add;

#define ADD_TESTCASE(name) \
    template struct TestSuite::Add<name>

#define TEST(name)                              \
    DECLARE_TESTCASE(name);                     \
    ADD_TESTCASE(name);                         \
    DEFINE_TESTCASE(name)

#define TESTMAIN()                              \
    int main(int argc, const char* argv[])      \
    {                                           \
        return TestSuite::run(argc, argv);      \
    }

#endif
