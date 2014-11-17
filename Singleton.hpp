#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "Debug.hpp"

template<typename T>
class Singleton
{
public:
    static T& instance()
    {
        static T object;

        return object;
    }

private:
    struct Init
    {
        Init()
        {
            DEBUG("Singleton::Init::Init()");
            instance();
        }
    };

    static Init s_init;
};

template<typename T>
typename Singleton<T>::Init
Singleton<T>::s_init;

#endif
