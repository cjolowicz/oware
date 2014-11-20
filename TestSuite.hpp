#ifndef TESTSUITE_HPP
#define TESTSUITE_HPP

#include "Singleton.hpp"
#include "TestCase.hpp"

#include <vector>

class TestSuite : public Singleton<TestSuite>
{
public:
    static void setName(const std::string& name);
    static void add(TestCase* testcase);
    static int run(int argc, const char* argv[]);

    TestSuite();
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
    void runTestCase(TestCase& testcase);

    std::string m_name;
    std::vector<TestCase*> m_testcases;
};

template<typename T>
TestSuite::Add<T>
TestSuite::Add<T>::s_add;

#define TESTSUITE_NAMESPACE(name) TestSuite_##name

#define ADD_TESTCASE(name) \
    template struct TestSuite::Add<TESTCASE_CLASS(name)>

#define TESTCASE(name)                          \
    DECLARE_TESTCASE(name);                     \
    ADD_TESTCASE(name);                         \
    DEFINE_TESTCASE(name)

#define TESTSUITE(name)                         \
    int main(int argc, const char* argv[])      \
    {                                           \
        TestSuite::setName(#name);              \
                                                \
        return TestSuite::run(argc, argv);      \
    }                                           \
                                                \
    namespace TESTSUITE_NAMESPACE(name)

#endif
