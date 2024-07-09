#pragma once

#include <stdbool.h>
#include "global_structs.h"
#include "piece.h"
#include "magicBoards.h"

#if defined(__GNUC__) || defined(__clang__)
#define ctz(x) __builtin_ctzll(x)
#elif defined(_MSC_VER)
#include <intrin.h>
#define ctz(x) (x == 0 ? sizeof(x) * 8 : sizeof(x) == 4 ? _tzcnt_u32(x) : _tzcnt_u64(x))
#else
#error "Unsupported compiler"
#endif




bool setFEN(char *FENstring);
bool isLegalMove(Square from, Square to);
GameStatus getGameStatus();

bool playMoveOnBoards(Square from, Square to, char promotionToPiece);
bool undoMovesOnBoards(int numberOfMoves);
bool isKingSafe();
void displayBitboard(Bitboard bitboard);
Bitboard getAllowedSquares(Square square);
MoveType getLatestMoveType() {