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

    void check_equal(const std::string& a, const std::string& b);
    void check_equal(int a, int b);
    void check_equal(unsigned int a, unsigned int b);

private:
    std::string m_name;
};

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
