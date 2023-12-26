#pragma once

#include "global_structs.h"

#define WHITE_BOUNDARY 'Z'

Color getColorByPiece(Piece p);
Piece getPieceByName(PieceName name, bool friendly);
Piece getPieceByColor(PieceName name, Color clr);
