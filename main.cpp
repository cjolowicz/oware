#include "Driver.hpp"
#include "Exception.hpp"

#include <stdio.h>

int main(int argc, const char* argv[])
{
    try
    {
        play(toMode(argc > 1 ? argv[1] : "ha"));
    }
    catch (const SystemExit&)
    {
        printf("\n");
        return 0;
    }
    catch (const Exception& exception)
    {
        fprintf(stderr, "%s", exception.what());

        return 1;
    }
    catch (...)
    {
        return 1;
    }

    return 0;
}
