#include "bitboards.h"
#include "magicBoardConstants.h"
#include "piece.h"

extern Boards __boards__;

// utility functions
inline static void setBit(Bitboard* bitboard, Square square)
{
    *bitboard |= 1UL << square;
}

inline static void clearBit(Bitboard* bitboard, Square square)
{
    *bitboard &= ~(1UL << square);
}

Bitboard* getBitboardForPiece(Piece piece)
{

    switch (piece)
    {
    case whiteKing:
        return &(__boards__.bitboards.whiteKing);
    case whiteQueen:
        return &(__boards__.bitboards.whiteQueens);
    case whiteRook:
        return &(__boards__.bitboards.whiteRooks);
    case whiteBishop:
        return &(__boards__.bitboards.whiteBishops);
    case whiteKnight:
        return &(__boards__.bitboards.whiteKnights);
    case whitePawn:
        return &(__boards__.bitboards.whitePawns);
    case blackKing:
        return &(__boards__.bitboards.blackKing);
    case blackQueen:
        return &(__boards__.bitboards.blackQueens);
    case blackRook:
        return &(__boards__.bitboards.blackRooks);
    case blackBishop:
        return &(__boards__.bitboards.blackBishops);
    case blackKnight:
        return &(__boards__.bitboards.blackKnights);
    case blackPawn:
        return &(__boards__.bitboards.blackPawns);
    }

    return 0;
}



void putPieceOnBitboard(Piece piece, Square square)
{
    Color c = getColorByPiece(piece);

    if(c == noColor) return;

    clearSquareOnBitboard(square);

    Bitboard* coloredPieces = (c == white)? &(__boards__.bitboards.whitePieces): &(__boards__.bitboards.blackPieces);

    setBit(getBitboardForPiece(piece), square);
    setBit(coloredPieces, square);
    setBit(&(__boards__.bitboards.occupiedBoard), square);
    setBit(&(__boards__.bitboards.occupiedRotated90LBoard), __occupied90L_shift__[square]);
    setBit(&(__boards__.bitboards.occupiedRotated45LBoard), __occupied45L_shift__[square]);
    setBit(&(__boards__.bitboards.occupiedRotated45RBoard), __occupied45R_shift__[square]); 
    return;
}

void clearSquareOnBitboard(Square square)
{
    Piece pieceToBeCleared = __boards__.board[square];

    if(pieceToBeCleared == nullPiece) return; // already a blank Square.


    Bitboard* coloredPieces = (getColorByPiece(pieceToBeCleared) == white)? &(__boards__.bitboards.whitePieces): &(__boards__.bitboards.blackPieces);

    clearBit(getBitboardForPiece(pieceToBeCleared), square);
    clearBit(coloredPieces, square);
    clearBit(&(__boards__.bitboards.occupiedBoard), square);
    clearBit(&(__boards__.bitboards.occupiedRotated90LBoard), __occupied90L_shift__[square]);
    clearBit(&(__boards__.bitboards.occupiedRotated45LBoard), __occupied45L_shift__[square]);
    clearBit(&(__boards__.bitboards.occupiedRotated45RBoard), __occupied45R_shift__[square]); 
    
    return;
}

void initBitboards()
{
    __boards__.bitboards.whitePawns = 0;
    __boards__.bitboards.blackPawns = 0;
    __boards__.bitboards.whiteKnights = 0;
    __boards__.bitboards.blackKnights = 0;
    __boards__.bitboards.whiteBishops = 0;
    __boards__.bitboards.blackBishops = 0;
    __boards__.bitboards.whiteRooks = 0;
    __boards__.bitboards.blackRooks = 0;
    __boards__.bitboards.whiteQueens = 0;
    __boards__.bitboards.blackQueens = 0;
    __boards__.bitboards.whiteKing = 0;
    __boards__.bitboards.blackKing = 0;
    __boards__.bitboards.blackPieces = 0;
    __boards__.bitboards.whitePieces = 0;
    __boards__.bitboards.occupiedBoard = 0;
    __boards__.bitboards.occupiedRotated90LBoard = 0;
    __boards__.bitboards.occupiedRotated45LBoard = 0;
    __boards__.bitboards.occupiedRotated45RBoard = 0;
}
