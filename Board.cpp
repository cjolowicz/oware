#include "Board.hpp"

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
