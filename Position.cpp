#include "Position.hpp"
#include "Assert.hpp"

#include <algorithm>

Position::Position(Board board, Player player)
    : m_player(player),
      m_board(board)
{
    ASSERT(MAX_COUNT ==
           total(PLAYER_A) +
           total(PLAYER_B) +
           score(PLAYER_A) +
           score(PLAYER_B));
}

Position::Position(BoardSide a, BoardSide b, Player player)
    : m_player(player),
      m_board(a, b)
{
    ASSERT(MAX_COUNT ==
           total(PLAYER_A) +
           total(PLAYER_B) +
           score(PLAYER_A) +
           score(PLAYER_B));
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

    Position previous = *this;

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
        if (previous.total(opponent()) == 0)
        {
            return false;
        }

        swap(previous);
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

        score(field.player) += content;

        content = 0;

        field.next();
    }
    while (field != initial);

    m_player = opponent();
}
