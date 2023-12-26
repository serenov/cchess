#include "global_structs.h"

Bitboard getSemiLegalMovesForSquare(Square square);
Bitboard getPseudoLegalMoves(Piece piece, Square square);
int get45LState(Square square);
int get45RState(Square square);
int getFileState(Square square);
int getRankState(Square square);