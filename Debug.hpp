#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifndef NDEBUG
#include <stdio.h>
#define DEBUG(...)                              \
    do                                          \
    {                                           \
        fprintf(stderr, "[DEBUG] ");            \
        fprintf(stderr, __VA_ARGS__);           \
        fprintf(stderr, "\n");                  \
        fflush(stderr);                         \
    }                                           \
    while (false)
#else
#define DEBUG(...)
#endif

#endif
