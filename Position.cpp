#include "Position.hpp"

#include <algorithm>
#include <limits>

const count_t INITIAL_COUNT = 4;
const count_t MAX_COUNT = 2 * (1+INDEX_6) * INITIAL_COUNT;
const count_t WIN_COUNT = MAX_COUNT / 2 + 1;

BoardSide::BoardSide()
    : score(0)
{
    fields[INDEX_1] = INITIAL_COUNT;
    fields[INDEX_2] = INITIAL_COUNT;
    fields[INDEX_3] = INITIAL_COUNT;
    fields[INDEX_4] = INITIAL_COUNT;
    fields[INDEX_5] = INITIAL_COUNT;
    fields[INDEX_6] = INITIAL_COUNT;
}

void BoardSide::swap(BoardSide& other)
{
    std::swap(score, other.score);
    std::swap(fields[INDEX_1], other.fields[INDEX_1]);
    std::swap(fields[INDEX_2], other.fields[INDEX_2]);
    std::swap(fields[INDEX_3], other.fields[INDEX_3]);
    std::swap(fields[INDEX_4], other.fields[INDEX_4]);
    std::swap(fields[INDEX_5], other.fields[INDEX_5]);
    std::swap(fields[INDEX_6], other.fields[INDEX_6]);
}

void Board::swap(Board& other)
{
    a.swap(other.a);
    b.swap(other.b);
}

Position::Position()
    : m_player(PLAYER_A),
      m_board()
{
}

void Position::swap(Position& other)
{
    std::swap(m_player, other.m_player);
    m_board.swap(other.m_board);
}

count_t Position::total(Player player) const
{
    count_t rv = 0;

    Field first = begin(player);
    Field last = end(player);

    while (first != last)
    {
        rv += count(first);

        first.next();
    }

    return rv;
}

bool Position::is_terminal() const
{
    return score(PLAYER_A) >= WIN_COUNT
        || score(PLAYER_B) >= WIN_COUNT;
}

bool Position::move_unsafe(Field field)
{
    if (field.player != player())
    {
        return false;
    }

    count_t& content = count(field);

    if (content == 0)
    {
        return false;
    }

    Field origin = field;

    while (content != 0)
    {
        field.next();

        if (field != origin)
        {
            count(field) += 1;

            content -= 1;
        }
    }

    count_t previous_score = score();

    while (field.player == opponent())
    {
        count_t& current = count(field);

        if (current < 2 || current > 3)
        {
            break;
        }

        score() += current;
        current = 0;

        field.previous();
    }

    if (total(opponent()) == 0)
    {
        return false;
    }

    m_player = opponent();

    return true;
}

void Position::finish_unsafe()
{
    Field initial = begin();
    Field field = initial;

    do
    {
        count_t& content = count(field);

        score(opponent_of(field.player)) += content;

        content = 0;

        field.next();
    }
    while (field != initial);
}

float evaluate(const Position& position)
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

float negamax(const Position& position, unsigned int depth)
{
    if (depth == 0 || position.is_terminal())
    {
        return evaluate(position);
    }

    bool can_move = false;

    float best = -1.0;

    Field first = position.begin();
    Field last = position.end();

    while (first != last)
    {
        std::pair<Position, bool> next = position.move(first);

        if (next.second)
        {
            best = std::max(best, -negamax(next.first, depth-1));

            can_move = true;
        }

        first.next();
    }

    if (!can_move)
    {
        Position next = position.finish();

        return -negamax(next, depth-1);
    }

    return best;
}
