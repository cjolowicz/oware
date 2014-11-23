#ifndef ASSERT_HPP
#define ASSERT_HPP

#include "Exception.hpp"

#include <assert.h>

#ifdef NDEBUG
#define ASSERT(expression)                              \
    do                                                  \
    {                                                   \
        if (!(expression))                              \
        {                                               \
            throw Exception(#expression, FILELINE);     \
        }                                               \
    }                                                   \
    while (false)
#else
#define ASSERT(expression) assert((expression))
#endif

#endif
