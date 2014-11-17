#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception(const std::string& what,
              const std::string& file,
              unsigned int line);

    virtual ~Exception() throw();
    virtual const char* what() const throw();

private:
    std::string m_what;
    std::string m_file;
    unsigned int m_line;
};

#define FILELINE __FILE__, __LINE__

#endif
