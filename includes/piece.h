#pragma once

#include "global_structs.h"

#define WHITE_BOUNDARY 'Z'

Color getColorByPiece(Piece p);
Piece getPieceByName(PieceName name, bool isFriendly);
Piece getPieceByColor(PieceName name, Color clr);
Color getColor(bool isFriendly);
