#include "Exception.hpp"

char to_digit(unsigned int value)
{
    switch (value)
    {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
    }

    return '?';
}

template<typename T>
std::string itostr(T value);

template<>
std::string itostr(unsigned int value)
{
    std::string result;

    do
    {
        std::string digit(to_digit(value % 10), 1);
        result = digit + result;

        value /= 10;
    }
    while (value != 0);

    return result;
}

Exception::Exception(const std::string& what,
                     const std::string& file,
                     unsigned int line)
    : m_what(what),
      m_file(file),
      m_line(line)
{
#ifndef NDEBUG
    m_what = m_file + ":" + itostr(m_line) + ": " + m_what;
#endif
}

Exception::~Exception() throw()
{
}

const char* Exception::what() const throw()
{
    return m_what.c_str();
}

