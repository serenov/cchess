#include "moves.h"
#include "piece.h"
#include "engine.h"
#include "magicBoardConstants.h"
#include "bitboards.h"

extern Boards __boards__;

static inline Bitboard generateKingMoves(Square square, bool isFriendly)
{
    // first generates the pseudo legalMoves
    Color c = getColor(isFriendly);

    Bitboard coloredPieces = (c == white)? __boards__.bitboards.whitePieces: __boards__.bitboards.blackPieces;

    return (~coloredPieces & ~(__boards__.state[__boards__.movesCount].allAttackedSquares) & __kingAttack__[square]);
}

static inline Bitboard generateKnightMoves(Square square, bool isFriendly)
{
    // first generates the pseudo legalMoves
    Color c = getColor(isFriendly);

    Bitboard coloredPieces = (c == white)? __boards__.bitboards.whitePieces: __boards__.bitboards.blackPieces;

    return (~coloredPieces & __knightAttack__[square]);
}

static inline Bitboard generateRookMoves(Square square, bool isFriendly)
{
    // first generates the pseudo legalMoves
    Color c = getColor(isFriendly);

    Bitboard coloredPieces = (c == white)? __boards__.bitboards.whitePieces: __boards__.bitboards.blackPieces;

    Bitboard MovesGenerated = __attackFile__[square][getFileState(square)] | __attackRank__[square][getRankState(square)];


    return (~coloredPieces & MovesGenerated);
}

static inline Bitboard generateBishopMoves(Square square, bool isFriendly)
{
    Color c = getColor(isFriendly);

    Bitboard coloredPieces = (c == white)? __boards__.bitboards.whitePieces: __boards__.bitboards.blackPieces;

    Bitboard MovesGenerated = __attackLeftDiagonal__[square][get45LState(square)] | __attackRightDiagonal__[square][get45RState(square)];


    return (~coloredPieces & MovesGenerated);
}

static inline Bitboard generatePawnMoves(Square square, bool isFriendly)
{
    Color c = getColor(isFriendly);


    Bitboard opponentPieces = (c == white)? __boards__.bitboards.blackPieces: __boards__.bitboards.whitePieces;
    Bitboard stepMove = (c == white)? 1UL << (square + 8): 1UL << (square - 8);
    Bitboard pawnMove = stepMove & ~(__boards__.bitboards.occupiedBoard);

    Bitboard movesGenerated = (__pawnAttack__[c][square] & opponentPieces) | pawnMove;


    if(pawnMove)
    {
        if(c == white)
        {
            if(square < 16) {
                movesGenerated |= ~(__boards__.bitboards.occupiedBoard) & (1UL << (square + 16));
            }
        }
        else 
        {
            if(square > 47) {
                movesGenerated |= ~(__boards__.bitboards.occupiedBoard) & (1UL << (square - 16));
            }
        }
    }

    return movesGenerated;
}

Bitboard getPseudoLegalMoves(Piece piece, Square square, bool isFriendly)
{
    switch (piece)
    {
    case whiteKing:
    case blackKing:
        return generateKingMoves(square, isFriendly);

    case whiteQueen:
    case blackQueen:
        return generateRookMoves(square, isFriendly) | generateBishopMoves(square, isFriendly);

    case whiteRook:
    case blackRook:
        return generateRookMoves(square, isFriendly);

    case whiteBishop:
    case blackBishop:
        return generateBishopMoves(square, isFriendly);

    case whiteKnight:
    case blackKnight:
        return generateKnightMoves(square, isFriendly);

    case blackPawn:
    case whitePawn:
        return generatePawnMoves(square, isFriendly);
    }
    return 0UL;
}

Bitboard getLegalMovesForSquare(Square square)
{
    Bitboard legalMoves = getPseudoLegalMoves(__boards__.board[square], square, true);
    if(__boards__.board[square] != whiteKing && __boards__.board[square] != blackKing)
        legalMoves &= getAllowedSquares(square);
    return legalMoves;
}

// Bitboard getLegalMoves(Square square)
// {
//     Piece p = __boards__.board[square];
//     Bitboard allowedSquares = ~(0UL);

//     if(p == nullPiece) return 0;

//     if(p == whiteKing || p == blackKing)
//     {
//         allowedSquares = (p == whiteKing)? ~(__boards__.state[__boards__.movesCount].blackAttackMask): ~(__boards__.state[__boards__.movesCount].whiteAttackMask);
//         return generateKingMoves(square) & allowedSquares;
//     }

//     if(!isKingSafe(__boards__.state[__boards__.movesCount].colorToPlay))
//     {
//         allowedSquares = 1;
//     }

// }



int getRankState(Square square)
{
    return ((__boards__.bitboards.occupiedBoard >> __occupied_skip__[square]) & 255);
}

int getFileState(Square square)
{
    return ((__boards__.bitboards.occupiedRotated90LBoard >> __occupied90L_skip__[square]) & 255);
}

int nBitString(int n)
{
    // returns 'n' 1's
    return (1 << n) - 1;
}

int get45LState(Square square)
{
    return (__boards__.bitboards.occupiedRotated45LBoard >> __occupied45L_skip__[square]) & nBitString(__occupied45L_diagonalLength__[square]);
}

int get45RState(Square square)
{
    return ((__boards__.bitboards.occupiedRotated45RBoard >> __occupied45R_skip__[square]) & nBitString(__occupied45R_diagonalLength__[square]));
}

