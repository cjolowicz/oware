#ifndef STRING_HPP
#define STRING_HPP

#include <string>

template<typename T>
std::string itostr(T value);

template<>
std::string itostr(unsigned int value);

template<>
std::string itostr(unsigned char value);

template<>
std::string itostr(int value);

template<typename T>
std::string ftostr(T value);

template<>
std::string ftostr(float value);

template<>
std::string ftostr(double value);

#endif
