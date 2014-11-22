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
    void check_close(double a, double b, double eta = 0.001);

private:
    std::string m_name;
};

#endif
