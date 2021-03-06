#ifndef BOARD_HPP
#define BOARD_HPP

typedef unsigned char count_t; // 0 to 48

extern const count_t INITIAL_COUNT;
extern const count_t MAX_COUNT;
extern const count_t WIN_COUNT;

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
    BoardSide(count_t i1 = INITIAL_COUNT,
              count_t i2 = INITIAL_COUNT,
              count_t i3 = INITIAL_COUNT,
              count_t i4 = INITIAL_COUNT,
              count_t i5 = INITIAL_COUNT,
              count_t i6 = INITIAL_COUNT,
              count_t score = 0);

    void swap(BoardSide& other);

    count_t fields[1+INDEX_6];
    count_t score;
};

struct Board
{
    Board();
    Board(BoardSide a, BoardSide b);

    void swap(Board& other);

    BoardSide a;
    BoardSide b;
};

inline
int compare(const BoardSide& a, const BoardSide& b)
{
    for (unsigned int i = 0; i < 6; ++i)
    {
        if (a.fields[i] < b.fields[i])
        {
            return -1;
        }

        if (a.fields[i] > b.fields[i])
        {
            return 1;
        }
    }

    return static_cast<int>(a.score) - b.score;
}

inline
int compare(const Board& a, const Board& b)
{
    int rv = compare(a.a, b.a);

    return rv != 0 ? rv : compare(a.b, b.b);
}

#endif
