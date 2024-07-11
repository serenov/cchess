#pragma once

typedef enum {

    black,
    white,
    noColor

} Color;

typedef enum {

    whiteKing = 'K',
    whiteQueen = 'Q',
    whiteRook = 'R',
    whiteBishop = 'B',
    whiteKnight = 'N',
    whitePawn = 'P',
    blackKing = 'k',
    blackQueen = 'q',
    blackRook = 'r',
    blackBishop = 'b',
    blackKnight = 'n',
    blackPawn = 'p',
    nullPiece = ' '
} Piece;

typedef enum {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
} PieceName;


