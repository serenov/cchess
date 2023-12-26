#include "engine.h"
#include "bitboards.h"
#include "moves.h"

#include "magicBoardConstants.h"

#include <stdlib.h>
#include <stdio.h>


#define DEFAULT_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
// #define DEFAULT_FEN "8/b1p2P2/2P3p1/2k5/2rp3n/4p2B/P1Pp4/6KN w - - 0 1"


// global board object
Boards __boards__;

void initPlainBoard()
{
    for (Square s = A1; s <= H8; s++)
    {
        __boards__.board[s] = nullPiece;
    }
}

static inline bool isWellFormedFEN(char *FENstring) {
    // TODO: implement this function.
    return true;
}

static inline void putPieceOnBoard(Piece p, Square s)
{
    __boards__.board[s] = p;
}

static inline void clearSquareOnBoard(Square s)
{
    __boards__.board[s] = nullPiece;
}


static inline int initBoards(char **FENstring)
{
    initPlainBoard();
    initBitboards();

    Square index = A8;

    while (**FENstring != ' ')
    {
        if (**FENstring == '/')
        {
            index -= 16;
        }
        else if (**FENstring >= '1' && **FENstring <= '8')
        {
            index += **FENstring - '0';
        }
        else
        {
            putPieceOnBoard((Piece)**FENstring, index);
            putPieceOnBitboard((Piece)**FENstring, index);

            index++;
        }

        *FENstring += 1;
    }
    *FENstring += 1;
}

#define INITIAL_COUNT 0

static inline void initTurn(char **FENstring)
{
    __boards__.state[INITIAL_COUNT].colorToPlay = (**FENstring == 'w')? white: black;
    *FENstring += 2;
}

static inline void initCastling(char **FENstring)
{
    for (Color c = black; c < noColor; c++)
    {
        __boards__.state[INITIAL_COUNT].canCastleLeft[c] = false;
        __boards__.state[INITIAL_COUNT].canCastleRight[c] = false;
    }

    if (**FENstring == 'K')
    {
        __boards__.state[INITIAL_COUNT].canCastleRight[1] = true;
        *FENstring += 1;
    }

    if (**FENstring == 'Q')
    {
        __boards__.state[INITIAL_COUNT].canCastleLeft[1] = true;
        *FENstring += 1;
    }

    if (**FENstring == 'k')
    {
        __boards__.state[INITIAL_COUNT].canCastleRight[0] = true;
        *FENstring += 1;
    }

    if (**FENstring == 'q')
    {
        __boards__.state[INITIAL_COUNT].canCastleLeft[0] = true;
        *FENstring += 1;
    }

    __boards__.state[INITIAL_COUNT].ignoreCastling[1] = !(__boards__.state[INITIAL_COUNT].canCastleLeft[1] || __boards__.state[INITIAL_COUNT].canCastleRight[1]);
    __boards__.state[INITIAL_COUNT].ignoreCastling[0] = !(__boards__.state[INITIAL_COUNT].canCastleLeft[0] || __boards__.state[INITIAL_COUNT].canCastleRight[0]);

    *FENstring += 1;
}

static inline void initEnpassant(char **FENstring)
{
    __boards__.state[INITIAL_COUNT].Enpassant = _null;

    if (**FENstring != '-')
    {
        __boards__.state[INITIAL_COUNT].Enpassant = (Square) **FENstring - 'a' + (*(*FENstring + 1) - '1') * 8;
        *FENstring += 3;
    }
    else *FENstring += 2;
}

static inline Bitboard iteratePiecesAndGenerateMoves(Bitboard bitboard, Piece piece)
{
    Bitboard movesGenerated = 0;

    while(bitboard != 0) {
        movesGenerated |= getPseudoLegalMoves(piece, ctz(bitboard));
        bitboard &= (bitboard - 1);
    }
}

Bitboard getAttackedSquares(Color c)
{
    Bitboard movesGenerated = 0;

    if(c == white)
    {
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.whiteKing, whiteKing);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.whiteQueens, whiteQueen);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.whiteBishops, whiteBishop);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.whiteRooks, whiteRook);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.whiteKnights, whiteKnight);
        movesGenerated |= ((__boards__.bitboards.whitePawns << 7) & ~__FILE__[0]) | ((__boards__.bitboards.whitePawns << 9) & ~__FILE__[7]);
    }
    else
    {
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.blackKing, blackKing);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.blackQueens, blackQueen);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.blackBishops, blackBishop);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.blackRooks, blackRook);
        movesGenerated |= iteratePiecesAndGenerateMoves(__boards__.bitboards.blackKnights, blackKnight);
        movesGenerated |= ((__boards__.bitboards.blackPawns << 7) & ~__FILE__[0]) | ((__boards__.bitboards.blackPawns << 9) & ~__FILE__[7]);
    }

    return movesGenerated;
}

void updateAttackedSquares() {
    __boards__.state[__boards__.movesCount].blackAttackMask = getAttackedSquares(black);
    __boards__.state[__boards__.movesCount].whiteAttackMask = getAttackedSquares(white);
}

bool setFEN(char *FENstring)
{
    if (!isWellFormedFEN(FENstring)) return false;
    if (FENstring == NULL) FENstring = DEFAULT_FEN;

    __boards__.movesCount = INITIAL_COUNT;

    initBoards(&FENstring);
    initTurn(&FENstring);
    initCastling(&FENstring);
    initEnpassant(&FENstring);
    updateAttackedSquares();

    return true;
}


void displayBitboard(Bitboard bitboard)
{
    Bitboard pos = 1UL;

    for (int y = 7; y > -1; y--)
    {

        printf("\n -------------------------------\n");
        for (int x = 0; x < 8; x++)
        {
            char c = ((pos << (y * 8 + x)) & bitboard) ? '*' : ' ';

            printf("| %c ", c);
        }
        printf("|");
    }
    printf("\n -------------------------------\n");
}



bool isLegalMove(Square from, Square to)
{
    Bitboard friendlyPieces = (__boards__.state[__boards__.movesCount].colorToPlay == white)? __boards__.bitboards.whitePieces: __boards__.bitboards.blackPieces;

    if((1UL << from) & friendlyPieces)
    {
        Bitboard movesGenerated = getSemiLegalMovesForSquare(from);
        displayBitboard(movesGenerated);

        if((1UL << to) & movesGenerated) return true;
    }

    return false;
}

GameStatus getGameStatus()
{
    return RUNNING;
}

static inline void updateGameStatus(Square from, Square to)
{
    Color c = __boards__.state[__boards__.movesCount].colorToPlay;

    __boards__.state[__boards__.movesCount].move.from = from;
    __boards__.state[__boards__.movesCount].move.to = to;
    __boards__.state[__boards__.movesCount].capturedPiece = __boards__.board[to];
    __boards__.movesCount++;
    __boards__.state[__boards__.movesCount].colorToPlay = !c;
}

bool playMoveOnBoards(Square from, Square to, char promotionToPiece)
{
    if(!isLegalMove(from, to)) return false;

    Piece movingPiece = __boards__.board[from];

    // Sequence of these operations must be preserved.

    updateGameStatus(from, to);

    putPieceOnBitboard(movingPiece, to);
    clearSquareOnBitboard(from);

    putPieceOnBoard(movingPiece, to);
    clearSquareOnBoard(from);

    updateAttackedSquares();

    return true;
}

bool isKingSafe(Color c) 
{
    if(c == white)
    {
        return (bool) (__boards__.bitboards.whiteKing & __boards__.state[__boards__.movesCount].blackAttackMask);
    }

    return (bool) (__boards__.bitboards.blackKing & __boards__.state[__boards__.movesCount].whiteAttackMask);
}




Bitboard getAllowedSquares(Square square)
{
    clearSquareOnBitboard(square);

    Bitboard kingBitboard = (__boards__.state[__boards__.movesCount].colorToPlay == white)? __boards__.bitboards.whiteKing: __boards__.bitboards.blackKing;
    Square kingSquare = ctz(kingBitboard);

    Bitboard leftDiagonal = __attackLeftDiagonal__[square][get45LState(square)];

    Bitboard rightDiagonal = __attackRightDiagonal__[square][get45RState(square)];

    Bitboard horizontal = __attackRank__[square][getRankState(square)];

    Bitboard vertical = __attackFile__[square][getFileState(square)];





}

