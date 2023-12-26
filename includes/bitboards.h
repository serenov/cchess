#pragma once

#include "global_structs.h"
#include <stdbool.h>

void initBitboards(); 

void putPieceOnBitboard(Piece piece, Square square);
void clearSquareOnBitboard(Square square);
Bitboard* getBitboardForPiece(Piece piece);