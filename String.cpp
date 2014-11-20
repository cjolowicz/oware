#include "String.hpp"

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

template<>
std::string itostr(unsigned int value)
{
    std::string result;

    do
    {
        std::string digit(1, to_digit(value % 10));
        result = digit + result;

        value /= 10;
    }
    while (value != 0);

    return result;
}

template<>
std::string itostr(unsigned char value)
{
    return itostr<unsigned int>(value);
}

template<>
std::string itostr(int value)
{
    if (value >= 0)
    {
        return itostr<unsigned int>(
            static_cast<unsigned int>(value));
    }

    return "-" + itostr<unsigned int>(
        static_cast<unsigned int>(value * -1));
}
