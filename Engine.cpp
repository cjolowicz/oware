#include "Engine.hpp"
#include "Driver.hpp"
#include "Exception.hpp"
#include "Debug.hpp"

#include <algorithm>
#include <utility>
#include <map>

namespace
{

void print_estimate(const Position& position, Field move, float best)
{
#ifdef DEBUG_ENGINE
    fprintf(stdout,
            ">%c%d "
            "[ %2d %2d %2d %2d %2d %2d  "
            "| %2d %2d %2d %2d %2d %2d  ] "
            "%2d  - %2d "
            "%5g\n",
            move.player == PLAYER_A ? 'A' : 'B',
            (int)move.index+1,
            (int)position.count(Field(PLAYER_A, INDEX_1)),
            (int)position.count(Field(PLAYER_A, INDEX_2)),
            (int)position.count(Field(PLAYER_A, INDEX_3)),
            (int)position.count(Field(PLAYER_A, INDEX_4)),
            (int)position.count(Field(PLAYER_A, INDEX_5)),
            (int)position.count(Field(PLAYER_A, INDEX_6)),
            (int)position.count(Field(PLAYER_B, INDEX_1)),
            (int)position.count(Field(PLAYER_B, INDEX_2)),
            (int)position.count(Field(PLAYER_B, INDEX_3)),
            (int)position.count(Field(PLAYER_B, INDEX_4)),
            (int)position.count(Field(PLAYER_B, INDEX_5)),
            (int)position.count(Field(PLAYER_B, INDEX_6)),
            (int)position.score(PLAYER_A),
            (int)position.score(PLAYER_B),
            (double)best);
#endif
}

} // namespace

const unsigned int Engine::DEFAULT_DEPTH = 8;

Engine::Cache::Entry::Entry(unsigned char depth, float value)
    : depth(depth), value(value)
{
}

bool Engine::Cache::lookup(const Position& position,
                           unsigned int depth,
                           float** value)
{
    value_type entry(position, Entry(static_cast<unsigned char>(depth), -1));

    std::pair<iterator, bool> result = m_entries.insert(entry);

    *value = &result.first->second.value;

    if (result.second || result.first->second.depth < depth)
    {
        result.first->second = entry.second;

        return false;
    }

    return true;
}

const std::string Engine::FileCache::DEFAULT_FILENAME("oware.cache");

Engine::FileCache::FileCache(const std::string& filename)
    : m_filename(filename)
{
    try
    {
        deserialize();
    }
    catch (const Exception& exception)
    {
        DEBUG("%s", exception.what());
    }
    catch (...)
    {
    }
}

Engine::FileCache::~FileCache()
{
    try
    {
        serialize();
    }
    catch (const Exception& exception)
    {
        DEBUG("%s", exception.what());
    }
    catch (...)
    {
    }
}

void Engine::FileCache::serialize()
{
    FILE* file = fopen(m_filename.c_str(), "w");

    if (file == 0)
    {
        throw Exception("cannot open " + m_filename + " for writing", FILELINE);
    }

    serialize(file);

    if (fclose(file) < 0)
    {
        throw Exception("cannot close " + m_filename + " after writing", FILELINE);
    }
}

void Engine::FileCache::serialize(FILE* file)
{
    const_iterator entry;
    for (entry = m_entries.begin();
         entry != m_entries.end(); ++entry)
    {
        serialize(file, *entry);
    }
}

void Engine::FileCache::serialize(FILE* file, const value_type& value)
{
    if (fwrite(&value, sizeof(value), 1, file) == 0)
    {
        throw Exception("cannot write to " + m_filename, FILELINE);
    }
}

void Engine::FileCache::deserialize()
{
    fprintf(stderr, "Loading cache...");

    FILE* file = fopen(m_filename.c_str(), "r");

    if (file == 0)
    {
        throw Exception("cannot open " + m_filename + " for reading", FILELINE);
    }

    deserialize(file);

    if (fclose(file) < 0)
    {
        throw Exception("cannot close " + m_filename + " after reading", FILELINE);
    }

    fprintf(stderr, " done.\n");
}

void Engine::FileCache::deserialize(FILE* file)
{
    value_type value;

    while (deserialize(file, value))
    {
        m_entries.insert(value);
    }
}

bool Engine::FileCache::deserialize(FILE* file, value_type& value)
{
    if (fread(&value, sizeof(value), 1, file) == 0)
    {
        if (ferror(file))
        {
            throw Exception("cannot read from " + m_filename, FILELINE);
        }

        return false;
    }

    return true;
}

Position Engine::move(const Position& position, Field& move)
{
    Field first = position.begin();
    Field last = position.end();

    std::pair<Position, float> best(position, -1.0);

    while (first != last)
    {
        std::pair<Position, bool> next = position.move(first);

        if (next.second)
        {
            float value = negamax(next.first);

            print_estimate(next.first, first, value);

            if (value > best.second)
            {
                best.first = next.first;
                best.second = value;

                move = first;
            }
        }

        first.next();
    }

    if (best.second == -1.0)
    {
        return position.finish();
    }

    return best.first;
}

float Engine::evaluate(const Position& position)
{
    float win = 1.0 * position.score() / WIN_COUNT;

    if (win >= 1.0)
    {
        return 1.0;
    }

    float defeat = -1.0 * position.score(position.opponent()) / WIN_COUNT;

    if (defeat <= -1.0)
    {
        return -1.0;
    }

    return win + defeat;
}

float Engine::negamax(const Position& position, unsigned int depth)
{
    float* best;

    if (m_cache.lookup(position, depth, &best))
    {
        return *best;
    }

    if (depth == 0 || position.is_terminal())
    {
        return *best = evaluate(position);
    }

    bool can_move = false;

    Field first = position.begin();
    Field last = position.end();

    while (first != last)
    {
        std::pair<Position, bool> next = position.move(first);

        if (next.second)
        {
            *best = std::max(*best, -negamax(next.first, depth-1));

            can_move = true;
        }

        first.next();
    }

    if (!can_move)
    {
        Position next = position.finish();

        *best = -negamax(next, depth-1);
    }

    return *best;
}
