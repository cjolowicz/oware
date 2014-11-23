#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Position.hpp"

#include <map>

class Engine
{
public:
    static const unsigned int DEFAULT_DEPTH;

    Position move(const Position& position);
    float negamax(const Position& position, unsigned int depth = DEFAULT_DEPTH);
    float evaluate(const Position& position);

private:
    class Cache
    {
    public:
        bool lookup(const Position& position,
                    unsigned int depth,
                    float** value);

    private:
        struct Entry
        {
            Entry(unsigned int depth, float value);

            unsigned int depth;
            float value;
        };

        typedef std::map<Position, Entry> map;
        typedef map::iterator iterator;
        typedef map::value_type value_type;

        map m_entries;
    };

    Cache m_cache;
};

#endif
