#include "global_structs.h"

Bitboard getLegalMovesForSquare(Square square);
Bitboard getPseudoLegalMoves(Piece piece, Square square, bool isFriendly);
int get45LState(Square square);
int get45RState(Square square);
int getFileState(Square square);
int getRankState(Square square);