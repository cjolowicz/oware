#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Agent.hpp"

#include <map>
#include <string>

#include <stdio.h>

class Engine : public Agent
{
public:
    static const unsigned int DEFAULT_DEPTH;

    virtual Position move(const Position& position, Field& move);
    float negamax(const Position& position, unsigned int depth = DEFAULT_DEPTH);
    float evaluate(const Position& position);

private:
    class Cache
    {
    public:
        bool lookup(const Position& position,
                    unsigned int depth,
                    float** value);

    protected:
        struct Entry
        {
            explicit Entry(unsigned char depth = 0, float value = 0.0);

            unsigned char depth;
            float value;
        };

        typedef std::map<Position, Entry> map;
        typedef map::iterator iterator;
        typedef map::const_iterator const_iterator;
        typedef map::value_type value_type;

        map m_entries;
    };

    class FileCache : public Cache
    {
    public:
        static const std::string DEFAULT_FILENAME;

        FileCache(const std::string& filename = DEFAULT_FILENAME);
        ~FileCache();

    private:
        void serialize();
        void deserialize();

        void serialize(FILE* file);
        void serialize(FILE* file, const value_type& value);

        void deserialize(FILE* file);
        bool deserialize(FILE* file, value_type& value);

        std::string m_filename;
    };

    FileCache m_cache;
};

#endif
