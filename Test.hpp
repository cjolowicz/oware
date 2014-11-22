#ifndef TEST_HPP
#define TEST_HPP

#include "TestRunner.hpp"
#include "TestSuite.hpp"
#include "TestCase.hpp"

#define TESTSUITE_NAMESPACE(name) TestSuite_##name

#define TESTCASE_NAMESPACE(name) TestCase_##name

#define OPEN_TESTSUITE_NAMESPACE(name) \
    namespace TESTSUITE_NAMESPACE(name)

#define OPEN_TESTCASE_NAMESPACE(name) \
    namespace TESTCASE_NAMESPACE(name)

#define DEFINE_TESTSUITE(name)                  \
    OPEN_TESTSUITE_NAMESPACE(name)              \
    {                                           \
        TestSuite testsuite(#name);             \
    }

#define DEFINE_TESTCASE(name)                   \
    OPEN_TESTCASE_NAMESPACE(name)               \
    {                                           \
        TestCase testcase(#name);               \
    }                                           \

#define DEFINE_TESTCASE_CLASS(name)             \
    OPEN_TESTCASE_NAMESPACE(name)               \
    {                                           \
        class TestCase : public ::TestCase      \
        {                                       \
        public:                                 \
            TestCase(const std::string& n);     \
                                                \
            virtual void run();                 \
        };                                      \
    }

#define DEFINE_TESTCASE_CTOR(name)                      \
    OPEN_TESTCASE_NAMESPACE(name)                       \
    {                                                   \
        TestCase::TestCase(const std::string& n)        \
            : ::TestCase(n)                             \
        {                                               \
            testsuite.add(*this);                       \
        }                                               \
    }

#define DEFINE_TESTCASE_RUN(name)               \
    void TESTCASE_NAMESPACE(name)::             \
    TestCase::run()

#define TESTSUITE(name)                         \
    DEFINE_TESTSUITE(name)                      \
    OPEN_TESTSUITE_NAMESPACE(name)

#define TESTCASE(name)                          \
    DEFINE_TESTCASE_CLASS(name)                 \
    DEFINE_TESTCASE(name)                       \
    DEFINE_TESTCASE_CTOR(name)                  \
    DEFINE_TESTCASE_RUN(name)

#endif
