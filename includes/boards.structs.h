#pragma once

#include <stdint.h>
#include "pieces.structs.h"
#include "squares.structs.h"
#include <stdbool.h>

typedef uint64_t Bitboard;
typedef Piece PlainBoard[64];

typedef struct
{
    Square from;
    Square to;
} Move;

typedef struct {

    Bitboard whitePawns;
    Bitboard blackPawns;

    Bitboard whiteKnights;
    Bitboard blackKnights;

    Bitboard whiteBishops;
    Bitboard blackBishops;

    Bitboard whiteRooks;
    Bitboard blackRooks;

    Bitboard whiteQueens;
    Bitboard blackQueens;

    Bitboard whiteKing;
    Bitboard blackKing;

    Bitboard blackPieces;
    Bitboard whitePieces;

    Bitboard occupiedBoard;
    Bitboard occupiedRotated90LBoard;
    Bitboard occupiedRotated45LBoard;
    Bitboard occupiedRotated45RBoard;

} Bitboards;

typedef enum {
    RUNNING,
    CHECKMATE,
    STALEMATE,
    DRAW
} GameStatus;

typedef enum {
    RegularMove,
    CastlingMove,
    EnpassantMove,
    promotionMove
} MoveType;

typedef struct 
{
    bool ignoreCastling[2];
    bool canCastleRight[2];
    bool canCastleLeft[2];
    
    Square Enpassant;
    GameStatus status;
    Color colorToPlay;
    Move move;
    Piece capturedPiece; // Recently Captured Piece
    Bitboard allAttackedSquares;
    MoveType typeOfMove;
} stateInfo;


typedef struct
{
    PlainBoard board;
    Bitboards bitboards;
    stateInfo state[1000]; // 1000 moves limit
    int movesCount;
}
Boards;