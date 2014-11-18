#ifndef TESTCASE_HPP
#define TESTCASE_HPP

#include "Exception.hpp"
#include "String.hpp"

class TestCase
{
public:
    explicit TestCase(const std::string& name);

    virtual ~TestCase();

    const std::string& name() const;

    virtual void run() = 0;

    void fail(const std::string& message);

    template<typename T>
    void check_equal(const T& a, const T& b);

private:
    std::string m_name;
};

template<>
void TestCase::check_equal(const std::string& a, const std::string& b);

template<typename T>
void TestCase::check_equal(const T& a, const T& b)
{
    if (!(a == b))
    {
        fail("expected " + itostr(b) + ", but got " + itostr(a));
    }
}

#define TESTCASE_CLASS(name) TestCase_##name

#define DECLARE_TESTCASE(name)                          \
    class TESTCASE_CLASS(name) : public TestCase        \
    {                                                   \
    public:                                             \
        TESTCASE_CLASS(name)();                         \
                                                        \
        virtual void run();                             \
    }

#define DEFINE_TESTCASE(name)                           \
    TESTCASE_CLASS(name)::TESTCASE_CLASS(name)()        \
        : TestCase(#name)                               \
    {                                                   \
    }                                                   \
                                                        \
    void TESTCASE_CLASS(name)::run()

#endif
