#ifndef TESTCASE_HPP
#define TESTCASE_HPP

#include <string>

class TestCase
{
public:
    explicit TestCase(const std::string& name);

    virtual ~TestCase();

    const std::string& name() const;

    virtual void run() = 0;

private:
    std::string m_name;
};

#define DECLARE_TESTCASE(name)                  \
    class name : public TestCase                \
    {                                           \
    public:                                     \
        name();                                 \
                                                \
        virtual void run();                     \
    }

#define DEFINE_TESTCASE(name)                   \
    name::name()                                \
        : TestCase(#name)                       \
    {                                           \
    }                                           \
                                                \
    void name::run()

#endif
