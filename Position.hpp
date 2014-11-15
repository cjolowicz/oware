#ifndef POSITION_HPP
#define POSITION_HPP

#include <algorithm>
#include <utility>

typedef unsigned char count_t; // 0 to 48

extern const count_t INITIAL_COUNT;

enum Player
{
    PLAYER_A,
    PLAYER_B
};

inline Player opponent_of(Player player)
{
    return player == PLAYER_A ? PLAYER_B : PLAYER_A;
}

enum Index
{
    INDEX_1,
    INDEX_2,
    INDEX_3,
    INDEX_4,
    INDEX_5,
    INDEX_6
};

struct BoardSide
{
    BoardSide();

    void swap(BoardSide& other);

    count_t fields[1+INDEX_6];
    count_t score;
};

struct Board
{
    void swap(Board& other);

    BoardSide a;
    BoardSide b;
};

struct Field
{
    Field(Player player = PLAYER_A, Index index = INDEX_1)
        : player(player),
          index(index)
    {
    }

    bool operator==(const Field& other) const
    {
        return player == other.player && index == other.index;
    }

    bool operator!=(const Field& other) const
    {
        return !operator==(other);
    }

    void next()
    {
        if (index == INDEX_6)
        {
            index = INDEX_1;
            player = opponent_of(player);
        }
        else
        {
            index = static_cast<Index>(index+1);
        }
    }

    void previous()
    {
        if (index == INDEX_1)
        {
            index = INDEX_6;
            player = opponent_of(player);
        }
        else
        {
            index = static_cast<Index>(index-1);
        }
    }

    Player player;
    Index index;
};

class Position
{
public:
    Position();

    void swap(Position& other);

    count_t total(Player player) const;

    bool is_terminal() const;

    Player player() const
    {
        return m_player;
    }

    Player opponent() const
    {
        return opponent_of(m_player);
    }

    count_t& score()
    {
        return score(player());
    }

    const count_t& score() const
    {
        return score(player());
    }

    count_t& score(Player player)
    {
        return player == PLAYER_A ? m_board.a.score : m_board.b.score;
    }

    const count_t& score(Player player) const
    {
        return player == PLAYER_A ? m_board.a.score : m_board.b.score;
    }

    count_t& count(Field field)
    {
        return field.player == PLAYER_A
            ? m_board.a.fields[field.index]
            : m_board.b.fields[field.index];
    }

    const count_t& count(Field field) const
    {
        return field.player == PLAYER_A
            ? m_board.a.fields[field.index]
            : m_board.b.fields[field.index];
    }

    bool has_move() const
    {
        Field first = begin();
        Field last = end();

        while (first != last)
        {
            if (move(first).second)
            {
                return true;
            }

            first.next();
        }

        return false;
    }

    std::pair<Position, bool> move(Field field) const
    {
        std::pair<Position, bool> next(*this, false);

        next.second = next.first.move_unsafe(field);

        return next;
    }

    std::pair<Position, bool> move(Index index) const
    {
        return move(Field(player(), index));
    }

    Position finish() const
    {
        Position next(*this);

        next.finish_unsafe();

        return next;
    }

    Field begin() const
    {
        return begin(player());
    }

    Field end() const
    {
        return end(player());
    }

    Field begin(Player player) const
    {
        return Field(player, INDEX_1);
    }

    Field end(Player player) const
    {
        return begin(opponent_of(player));
    }

private:
    bool move_unsafe(Field field);
    void finish_unsafe();

    Player m_player;
    Board m_board;
};

float evaluate(const Position& position);
float negamax(const Position& position, unsigned int depth);

#endif
