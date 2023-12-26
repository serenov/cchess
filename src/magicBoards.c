#include "magicBoards.h"
// Magic Boards for rotated 45 degrees board
const unsigned char __occupied45R_shift__[64] = {
    35, 27, 20, 14,  9,  5,  2,  0,
    42, 34, 26, 19, 13,  8,  4,  1,
    48, 41, 33, 25, 18, 12,  7,  3,
    53, 47, 40, 32, 24, 17, 11,  6,
    57, 52, 46, 39, 31, 23, 16, 10,
    60, 56, 51, 45, 38, 30, 22, 15,
    62, 59, 55, 50, 44, 37, 29, 21,
    63, 61, 58, 54, 49, 43, 36, 28
};
const unsigned char __occupied45R_diagonalLength__[64] = {
    8, 7, 6, 5, 4, 3, 2, 1,
    7, 8, 7, 6, 5, 4, 3, 2,
    6, 7, 8, 7, 6, 5, 4, 3,
    5, 6, 7, 8, 7, 6, 5, 4,
    4, 5, 6, 7, 8, 7, 6, 5,
    3, 4, 5, 6, 7, 8, 7, 6,
    2, 3, 4, 5, 6, 7, 8, 7,
    1, 2, 3, 4, 5, 6, 7, 8
};
const unsigned char __occupied45R_skip__[64] = {
    28, 21, 15, 10,  6,  3,  1,  0,
    36, 28, 21, 15, 10,  6,  3,  1,
    43, 36, 28, 21, 15, 10,  6,  3,
    49, 43, 36, 28, 21, 15, 10,  6,
    54, 49, 43, 36, 28, 21, 15, 10,
    58, 54, 49, 43, 36, 28, 21, 15,
    61, 58, 54, 49, 43, 36, 28, 21,
    63, 61, 58, 54, 49, 43, 36, 28
};

// Magic Boards for rotated 45 degrees board
const unsigned char __occupied45L_shift__[64] = {
     0,  2,  5,  9, 14, 20, 27, 35,
     1,  4,  8, 13, 19, 26, 34, 42,
     3,  7, 12, 18, 25, 33, 41, 48,
     6, 11, 17, 24, 32, 40, 47, 53,
    10, 16, 23, 31, 39, 46, 52, 57,
    15, 22, 30, 38, 45, 51, 56, 60,
    21, 29, 37, 44, 50, 55, 59, 62,
    28, 36, 43, 49, 54, 58, 61, 63
};

const unsigned char __occupied45L_diagonalLength__[64] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    2, 3, 4, 5, 6, 7, 8, 7,
    3, 4, 5, 6, 7, 8, 7, 6,
    4, 5, 6, 7, 8, 7, 6, 5,
    5, 6, 7, 8, 7, 6, 5, 4,
    6, 7, 8, 7, 6, 5, 4, 3,
    7, 8, 7, 6, 5, 4, 3, 2,
    8, 7, 6, 5, 4, 3, 2, 1
};

const unsigned char __occupied45L_skip__[64] = {
     0,  1,  3,  6, 10, 15, 21, 28,
     1,  3,  6, 10, 15, 21, 28, 36,
     3,  6, 10, 15, 21, 28, 36, 43,
     6, 10, 15, 21, 28, 36, 43, 49,
    10, 15, 21, 28, 36, 43, 49, 54,
    15, 21, 28, 36, 43, 49, 54, 58,
    21, 28, 36, 43, 49, 54, 58, 61,
    28, 36, 43, 49, 54, 58, 61, 63
};

// magic Board for rotated 90 Degrees Board

const unsigned char __occupied90L_shift__[64] = {
    7, 15, 23, 31, 39, 47, 55, 63,
    6, 14, 22, 30, 38, 46, 54, 62,
    5, 13, 21, 29, 37, 45, 53, 61,
    4, 12, 20, 28, 36, 44, 52, 60,
    3, 11, 19, 27, 35, 43, 51, 59,
    2, 10, 18, 26, 34, 42, 50, 58,
    1,  9, 17, 25, 33, 41, 49, 57,
    0,  8, 16, 24, 32, 40, 48, 56
};

const unsigned char __occupied90L_skip__[64] = {
    0, 8, 16, 24, 32, 40, 48, 56,
    0, 8, 16, 24, 32, 40, 48, 56,
    0, 8, 16, 24, 32, 40, 48, 56,
    0, 8, 16, 24, 32, 40, 48, 56,
    0, 8, 16, 24, 32, 40, 48, 56,
    0, 8, 16, 24, 32, 40, 48, 56,
    0, 8, 16, 24, 32, 40, 48, 56,
    0, 8, 16, 24, 32, 40, 48, 56
};

// magic board for 0 Degrees Board

const unsigned char __occupied_skip__[64] = {
     0,  0,  0,  0,  0,  0,  0,  0,
     8,  8,  8,  8,  8,  8,  8,  8,
    16, 16, 16, 16, 16, 16, 16, 16,
    24, 24, 24, 24, 24, 24, 24, 24,
    32, 32, 32, 32, 32, 32, 32, 32,
    40, 40, 40, 40, 40, 40, 40, 40,
    48, 48, 48, 48, 48, 48, 48, 48,
    56, 56, 56, 56, 56, 56, 56, 56
};



// attack patterns for pieces

Bitboard __kingAttack__[64];
Bitboard __knightAttack__[64];
Bitboard __pawnAttack__[2][64];
Bitboard __attackRank__[64][256];
Bitboard __attackFile__[64][256];
Bitboard __attackRightDiagonal__[64][256];
Bitboard __attackLeftDiagonal__[64][256];


// ranks & files
Bitboard __ranks__[8];
Bitboard __files__[8];

// Initializationss

const Bitboard A1Square = 1;
const Bitboard H8Square = 1UL << 63;


static inline void initPawnAttacks()
{

    const Bitboard fileA = __files__[0], fileH = __files__[7];

    for (Square sq = A1; sq <= H8; sq = (Square)(sq + 1))
    {

        __pawnAttack__[white][sq] = 0;
        __pawnAttack__[black][sq] = 0;

        Bitboard p = A1Square << sq;

        if (~fileA & p)
        {
            __pawnAttack__[white][sq] |= p << 7;
            __pawnAttack__[black][sq] |= p >> 9;
        }

        if (~fileH & p)
        {
            __pawnAttack__[white][sq] |= p << 9;
            __pawnAttack__[black][sq] |= p >> 7;
        }
    }
}

static inline void initKnightAttack()
{

    const Bitboard fileA = __files__[0], fileH = __files__[7];
    const Bitboard fileAB = __files__[1] | fileA, fileGH = __files__[6] | fileH;

    for (Square sq = A1; sq <= H8; sq = (Square)(sq + 1))
    {

        Bitboard p = A1Square << sq;

        __knightAttack__[sq] = 0;

        if (~fileA & p)
        {
            __knightAttack__[sq] |= p << 15;
            __knightAttack__[sq] |= p >> 17;
        }

        if (~fileAB & p)
        {
            __knightAttack__[sq] |= p << 6;
            __knightAttack__[sq] |= p >> 10;
        }

        if (~fileH & p)
        {
            __knightAttack__[sq] |= p << 17;
            __knightAttack__[sq] |= p >> 15;
        }

        if (~fileGH & p)
        {
            __knightAttack__[sq] |= p << 10;
            __knightAttack__[sq] |= p >> 6;
        }
    }
}

static inline void initKingAttack()
{

    const Bitboard fileA = __files__[0], fileH = __files__[7];
    // const Bitboard rank1 = __ranks__[0], rank8 = __ranks__[7];

    for (Square sq = A1; sq <= H8; sq = (Square)(sq + 1))
    {

        __kingAttack__[sq] = 0;

        Bitboard p = A1Square << sq;

        __kingAttack__[sq] |= p << 8;
        __kingAttack__[sq] |= p >> 8;

        if (~fileA & p)
        {
            __kingAttack__[sq] |= p << 7;
            __kingAttack__[sq] |= p >> 1;
            __kingAttack__[sq] |= p >> 9;
        }

        if (~fileH & p)
        {
            __kingAttack__[sq] |= p >> 7;
            __kingAttack__[sq] |= p << 1;
            __kingAttack__[sq] |= p << 9;
        }
    }
}

static inline void initAttackRank()
{

    for (Square sq = A1; sq <= H8; sq = (Square)(sq + 1))
    {

        int x = sq % 8, y = sq / 8;

        Bitboard p = A1Square << sq;

        unsigned char start = 1 << x;

        for (unsigned char state = 1; ; state++)
        {

            __attackRank__[sq][state] = 0;

            for (int i = 1; i <= x; i++)
            {

                __attackRank__[sq][state] |= p >> i;
                if ((start >> i) & state)
                    break;
            }

            for (int i = 1; i <= 7 - x; i++)
            {

                __attackRank__[sq][state] |= p << i;
                if ((start << i) & state)
                    break;
            }

            if(state == 255) break;

        }

    }
}

static inline void initAttackFile()
{

    for (Square sq = A1; sq <= H8; sq = (Square)(sq + 1))
    {

        Bitboard p = A1Square << sq;

        int x = sq % 8, y = sq / 8;

        for (unsigned char state = 1; ; state++)
        {

            __attackFile__[sq][state] = 0;

            unsigned char start = 1 << (7 - y);

            for (int i = 1; i <= y; i++)
            {

                __attackFile__[sq][state] |= p >> (i * 8);
                if ((start << i) & state)
                    break;
            }

            for (int i = 1; i <= 7 - y; i++)
            {

                __attackFile__[sq][state] |= p << (i * 8);
                if ((start >> i) & state)
                    break;
            }

            if(state == 255) break;
        }
    }
}

static inline void initAttackRightDiagonal()
{

    for (Square sq = A1; sq <= H8; sq = (Square)(sq + 1))
    {

        Bitboard pos = A1Square << sq;

        int limit = 1 << __occupied45R_diagonalLength__[sq];

        unsigned char start = 1 << (__occupied45R_shift__[sq] - __occupied45R_skip__[sq]);

        for (int state = 1; state < limit; state++)
        {

            __attackRightDiagonal__[sq][state] = 0;

            for (int i = 1; i <= (__occupied45R_shift__[sq] - __occupied45R_skip__[sq]); i++)
            {

                __attackRightDiagonal__[sq][state] |= pos << (i * 9);
                if ((start >> i) & state)
                    break;
            }

            for (int i = 1; i < ((__occupied45R_skip__[sq] + __occupied45R_diagonalLength__[sq]) - __occupied45R_shift__[sq]); i++)
            {

                __attackRightDiagonal__[sq][state] |= pos >> (i * 9);
                if ((start << i) & state)
                    break;
            }
        }
    }
}

static inline void initAttackLeftDiagonal()
{

    for (Square sq = A1; sq <= H8; sq = (Square)(sq + 1))
    {

        Bitboard pos = A1Square << sq;

        int limit = 1 << __occupied45L_diagonalLength__[sq];

        unsigned char start = 1 << (__occupied45L_shift__[sq] - __occupied45L_skip__[sq]);

        for (int state = 1; state < limit; state++)
        {

            __attackLeftDiagonal__[sq][state] = 0;

            for (int i = 1; i <= (__occupied45L_shift__[sq] - __occupied45L_skip__[sq]); i++)
            {

                __attackLeftDiagonal__[sq][state] |= pos << (i * 7);
                if ((start >> i) & state)
                    break;
            }

            for (int i = 1; i < ((__occupied45L_skip__[sq] + __occupied45L_diagonalLength__[sq]) - __occupied45L_shift__[sq]); i++)
            {

                __attackLeftDiagonal__[sq][state] |= pos >> (i * 7);
                if ((start << i) & state)
                    break;
            }
        }
    }
}

static inline void initRanksAndFiles()
{

    for (int i = 0; i < 8; i++)
    {
        __ranks__[i] = 255UL << i * 8;
        __files__[i] = 72340172838076673UL << i;
    }
}

inline int getRankState(Boards *boards, Square square)
{
    return ((boards->bitboards.occupiedBoard) << __occupied_skip__[square]) & 255;
}
inline int getFileState(Boards *boards, Square square)
{
    return ((boards->bitboards.occupiedBoard) << __occupied90L_skip__[square]) & 255;
}
inline int getRDiagonal(Boards *boards, Square square)
{
    return ((boards->bitboards.occupiedBoard) << __occupied45R_skip__[square]) & ((1 << __occupied45R_diagonalLength__[square]) - 1);
}
inline int getLDiagonal(Boards *boards, Square square)
{
    return ((boards->bitboards.occupiedBoard) << __occupied45L_skip__[square]) & ((1 << __occupied45L_diagonalLength__[square]) - 1);
}

void initMagicBoards()
{
    initRanksAndFiles();
    initKingAttack();
    initKnightAttack();
    initPawnAttacks();

    initAttackRank();
    initAttackFile();

    initAttackLeftDiagonal();
    initAttackRightDiagonal();
}


