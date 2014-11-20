#include "Position.hpp"

#include <algorithm>

const count_t INITIAL_COUNT = 4;
const count_t MAX_COUNT = 2 * (1+INDEX_6) * INITIAL_COUNT;
const count_t WIN_COUNT = MAX_COUNT / 2 + 1;

BoardSide::BoardSide(count_t i1,
                     count_t i2,
                     count_t i3,
                     count_t i4,
                     count_t i5,
                     count_t i6,
                     count_t score)
    : score(score)
{
    fields[INDEX_1] = i1;
    fields[INDEX_2] = i2;
    fields[INDEX_3] = i3;
    fields[INDEX_4] = i4;
    fields[INDEX_5] = i5;
    fields[INDEX_6] = i6;
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

Board::Board()
    : a(),
      b()
{
}

Board::Board(BoardSide a, BoardSide b)
    : a(a),
      b(b)
{
}

void Board::swap(Board& other)
{
    a.swap(other.a);
    b.swap(other.b);
}

Position::Position(Board board, Player player)
    : m_player(player),
      m_board(board)
{
}

Position::Position(BoardSide a, BoardSide b, Player player)
    : m_player(player),
      m_board(a, b)
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
