#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Position.hpp"

#include <map>
#include <string>

#include <stdio.h>

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

    protected:
        struct Entry
        {
            explicit Entry(unsigned int depth = 0, float value = 0.0);

            unsigned int depth;
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
        void serialize(FILE* file,
                       const Position& position,
                       const Entry& entry);
        void serialize(FILE* file,
                       const char* buffer,
                       size_t bufferSize);

        void deserialize(FILE* file);
        bool deserialize(FILE* file,
                         Position& position,
                         Entry& entry);
        bool deserialize(FILE* file,
                         char* buffer,
                         size_t bufferSize);

        std::string m_filename;
    };

    FileCache m_cache;
};

#endif
