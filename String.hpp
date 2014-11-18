#ifndef STRING_HPP
#define STRING_HPP

#include <string>

template<typename T>
std::string itostr(T value);

template<>
std::string itostr(unsigned int value);

#endif
