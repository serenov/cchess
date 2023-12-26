#pragma once

#include "global_structs.h"


// Magic Boards for rotated 45 degrees board
extern const unsigned char __occupied45R_shift__[64];

extern const unsigned char __occupied45R_diagonalLength__[64];

extern const unsigned char __occupied45R_skip__[64];



// Magic Boards for rotated 45 degrees board
extern const unsigned char __occupied45L_shift__[64];

extern const unsigned char __occupied45L_diagonalLength__[64];

extern const unsigned char __occupied45L_skip__[64];


// magic Board for rotated 90 Degrees Board

extern const unsigned char __occupied90L_shift__[64];

extern const unsigned char __occupied90L_skip__[64];

// magic board for 0 Degrees Board

extern const unsigned char __occupied_skip__[64];

// attack patterns for pieces

extern Bitboard __kingAttack__[64];
extern Bitboard __knightAttack__[64];
extern Bitboard __pawnAttack__[2][64];
extern Bitboard __attackRank__[64][256];
extern Bitboard __attackFile__[64][256];
extern Bitboard __attackRightDiagonal__[64][256];
extern Bitboard __attackLeftDiagonal__[64][256];


// ranks & files
extern Bitboard __ranks__[8];
extern Bitboard __files__[8];