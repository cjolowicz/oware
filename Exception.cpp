#include "Exception.hpp"
#include "String.hpp"

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

SystemExit::SystemExit()
    : Exception("exit", FILELINE)
{
}
