#include "engine.h"
#include "bitboards.h"
#include "moves.h"
#include "piece.h"

#include "magicBoardConstants.h"

#include <stdlib.h>
#include <stdio.h>


#define DEFAULT_FEN "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - "
// #define DEFAULT_FEN "rn1qkbnr/pppR1ppp/8/8/1b6/8/PPPPP1PP/RNBQKBNR b KQkq - 0 1"
// #define DEFAULT_FEN "8/b1p2P2/2P3p1/2k5/2rp3n/4p2B/P1Pp4/6KN w - - 0 1"


// global board object
Boards __boards__;

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

static inline Bitboard iteratePiecesAndGenerateMoves(Piece piece)
{
    Bitboard bitboard = *(getBitboardForPiece(piece));
    
    // displayBitboard(bitboard);

    Bitboard movesGenerated = 0;

    while(bitboard != 0) {
        movesGenerated |= getPseudoLegalMoves(piece, ctz(bitboard), false);
        // displayBitboard(movesGenerated);
        bitboard &= (bitboard - 1);
    }

    return movesGenerated;
}

static inline Bitboard getPawnAttackMask()
{
    Bitboard pawns = *(getBitboardForPiece(getPieceByName(Pawn, false)));

    
    return (getColor(false) == white)?
    ((pawns & ~(__files__[0])) << 7) | ((pawns & ~(__files__[7])) << 9):
    ((pawns & ~(__files__[0])) >> 9) | ((pawns & ~(__files__[7])) >> 7);
}

Bitboard getAttackedSquares()
{
    Bitboard attackedSquares = 0;

    attackedSquares |= iteratePiecesAndGenerateMoves(getPieceByName(King, false));
    attackedSquares |= iteratePiecesAndGenerateMoves(getPieceByName(Queen, false));
    attackedSquares |= iteratePiecesAndGenerateMoves(getPieceByName(Rook, false));
    attackedSquares |= iteratePiecesAndGenerateMoves(getPieceByName(Bishop, false));
    attackedSquares |= iteratePiecesAndGenerateMoves(getPieceByName(Knight, false));

    attackedSquares |= getPawnAttackMask();


    // displayBitboard(attackedSquares);

    return attackedSquares;
}

void updateAttackedSquares() {
   
   __boards__.state[__boards__.movesCount].allAttackedSquares = getAttackedSquares();
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


bool isLegalMove(Square from, Square to)
{
    Bitboard friendlyPieces = (getColor(true) == white)? __boards__.bitboards.whitePieces: __boards__.bitboards.blackPieces;

    if((1UL << from) & friendlyPieces)
    {
        Bitboard movesGenerated = getLegalMovesForSquare(from);
        // displayBitboard(movesGenerated);

        if((1UL << to) & movesGenerated) return true;
    }

    return false;
}

GameStatus getGameStatus()
{
    return __boards__.state[__boards__.movesCount].status;
}

static inline bool isThereAnyLegalMove()
{
    Color clr = getColor(true);

    Bitboard coloredPieces = (clr == white)? __boards__.bitboards.whitePieces: __boards__.bitboards.blackPieces;

    while (coloredPieces)
    {
        if(getLegalMovesForSquare(ctz(coloredPieces))) return true;
        coloredPieces &= (coloredPieces - 1);
    }

    return false;
    
}

void updateGameStatus()
{
    GameStatus status = RUNNING;

    if(!isThereAnyLegalMove())
    {
        if(isKingSafe()) {
            status = STALEMATE;
        }
        else {
            status = CHECKMATE;
        }
    }

    __boards__.state[__boards__.movesCount].status = status;
}

void handleEnpassant(Square from, Square to, Piece* movingPiece) {

    if(__boards__.state[__boards__.movesCount].Enpassant == to)
    {
        // Enpassant move handling.
        Square attackedSquare = _null;
        Piece capturedPiece = nullPiece;

        if(*movingPiece == whitePawn)
        {
            attackedSquare = to - 8;
            capturedPiece = blackPawn;
        }
        else if(*movingPiece == blackPawn)
        {
            attackedSquare = to + 8;
            capturedPiece = whitePawn;
        }

        if(attackedSquare != _null) {
            __boards__.state[__boards__.movesCount].typeOfMove = EnpassantMove;
            __boards__.state[__boards__.movesCount].capturedPiece = capturedPiece;

            clearSquareOnBoard(attackedSquare);
            clearSquareOnBitboard(attackedSquare);
        }
    }
}

static inline void updateBoardStatus(Square from, Square to)
{
    __boards__.state[__boards__.movesCount].typeOfMove = RegularMove;
    __boards__.state[__boards__.movesCount].move.from = from;
    __boards__.state[__boards__.movesCount].move.to = to;

    __boards__.state[__boards__.movesCount].capturedPiece = __boards__.board[to];

    Piece movingPiece = __boards__.board[from];

    handleEnpassant(from, to, &movingPiece);

    Color c = getColor(true);



    __boards__.movesCount++;

    __boards__.state[__boards__.movesCount].colorToPlay = !c;

    // updating enpassant status.

    Square enpassantSquare = _null;

    if (movingPiece == whitePawn || movingPiece == blackPawn) {
        if(abs(from - to) == 16) {
            enpassantSquare = (movingPiece == whitePawn)? from + 8: from - 8;
        }
    }

    __boards__.state[__boards__.movesCount].Enpassant = enpassantSquare;
}


bool playMoveOnBoards(Square from, Square to, char promotionToPiece)
{
    if(!isLegalMove(from, to)) return false;

    Piece movingPiece = __boards__.board[from];

    // Sequence of these operations must be preserved.


    updateBoardStatus(from, to);

    putPieceOnBitboard(movingPiece, to);
    clearSquareOnBitboard(from);

    putPieceOnBoard(movingPiece, to);
    clearSquareOnBoard(from);


    updateAttackedSquares();

    updateGameStatus();

    return true;
}

void undoLastMove()
{
    int movecnt = __boards__.movesCount - 1;

    MoveType mvtype = __boards__.state[movecnt].typeOfMove;
    Move mv = __boards__.state[movecnt].move;

    Piece p = __boards__.board[mv.to];
    Piece capturedP = __boards__.state[movecnt].capturedPiece;

    putPieceOnBitboard(p, mv.from);
    clearSquareOnBitboard(mv.to);

    if(mvtype == RegularMove) 
    {
        //sequence of operations must be preserved please.
        if(capturedP != nullPiece) putPieceOnBitboard(capturedP, mv.to);

        putPieceOnBoard(p, mv.from);
        putPieceOnBoard(capturedP, mv.to);

    }
    else if(mvtype == EnpassantMove) 
    {
        //sequence of operations must be preserved please.
        putPieceOnBitboard(capturedP, (capturedP == whitePawn) ? mv.to + 8 : mv.to - 8);

        putPieceOnBoard(p, mv.from);
        clearSquareOnBoard(mv.to);
        putPieceOnBoard(capturedP, (capturedP == whitePawn) ? mv.to + 8 : mv.to - 8);

    }

    __boards__.movesCount -= 1;
}

bool isKingSafe() 
{
    Bitboard* kingBitboard = getBitboardForPiece(getPieceByName(King, true));

    // displayBitboard(__boards__.state[__boards__.movesCount].allAttackedSquares);

    return !(*kingBitboard & __boards__.state[__boards__.movesCount].allAttackedSquares);
}


#define ALL_SQUARES ~(0UL)


static inline Bitboard automation(Square kingSquare, Bitboard *pattern, Bitboard pieceBoard, int length)
{
    // TODO: come up with better names

    for(int i = 0; i < length; i++)
    {
        if(pattern[i] & pieceBoard) 
        {

            int index = ctz(pattern[i] & pieceBoard);

            // displayBitboard(pattern[i]);


            Bitboard returnVal = (kingSquare > index)? (pattern[i] << (63 - kingSquare)):  (pattern[i] >> (kingSquare));
            // displayBitboard(returnVal);
            returnVal = (kingSquare > index)? (returnVal >> (63 - kingSquare)):  (returnVal << (kingSquare));

            // displayBitboard(returnVal);
            return returnVal;
        }
    }

    return 0;

}

MoveType getLatestMoveType() {
    return __boards__.state[__boards__.movesCount - 1].typeOfMove;
}


Bitboard getAllowedSquares(Square square)
{
    // Note: Assumption -> Only one or more distinct piece(s) can attack king at a time.
    // This might not be true for unnatural positions.
    // i.e., white to play and white king attacked by two black knights.
    // such position can never be achieved by standard gameplay, thus unnatural.

    // TODO: modify the logic to cover such edge cases.

    Bitboard* kingBitboard = getBitboardForPiece(getPieceByName(King, true));
    Square kingSquare = ctz(*kingBitboard);

    if(square == kingSquare) return ALL_SQUARES; 

    // assert board[square] != empty

    Piece clearedPiece = __boards__.board[square];

    clearSquareOnBitboard(square);

    Bitboard leftDiagonal = __attackLeftDiagonal__[kingSquare][get45LState(kingSquare)];
    Bitboard rightDiagonal = __attackRightDiagonal__[kingSquare][get45RState(kingSquare)];
    Bitboard horizontal = __attackRank__[kingSquare][getRankState(kingSquare)];
    Bitboard vertical = __attackFile__[kingSquare][getFileState(kingSquare)];
    Bitboard knightPattern = __knightAttack__[kingSquare];
    Bitboard pawnPattern = __pawnAttack__[getColor(true)][kingSquare];

    Bitboard* queenBitboard = getBitboardForPiece(getPieceByName(Queen, false));
    Bitboard* rookBitboard = getBitboardForPiece(getPieceByName(Rook, false));
    Bitboard* bishopBitboard = getBitboardForPiece(getPieceByName(Bishop, false));
    Bitboard* knightBitboard = getBitboardForPiece(getPieceByName(Knight, false));
    Bitboard* pawnBitboard = getBitboardForPiece(getPieceByName(Pawn, false));

    putPieceOnBitboard(clearedPiece, square);

    int maxChecks = 5;

    Bitboard lineOfAttack = 0;


    Bitboard queenPattern[] = { leftDiagonal, rightDiagonal, horizontal, vertical };

    Bitboard queenAttack = automation(kingSquare, queenPattern, *queenBitboard, 4);

    if(queenAttack) 
    {
        lineOfAttack |= queenAttack;
    }
    else maxChecks--;


    Bitboard rookPattern[] = { horizontal, vertical };

    Bitboard rookAttack = automation(kingSquare, rookPattern, *rookBitboard, 2);

    if(rookAttack) 
    {
        lineOfAttack |= rookAttack;
    }
    else maxChecks--;



    Bitboard bishopPattern[] = { leftDiagonal, rightDiagonal };

    Bitboard bishopAttack = automation(kingSquare, bishopPattern, *bishopBitboard, 2);

    if(bishopAttack) 
    {
        lineOfAttack |= bishopAttack;
    }
    else maxChecks--;



    if(*knightBitboard & knightPattern) {
        lineOfAttack |= (knightPattern & *knightBitboard);
    }
    else maxChecks--;


    if(*pawnBitboard & pawnPattern) {
        lineOfAttack |= (*pawnBitboard & pawnPattern);
    }
    else maxChecks--;


    if(maxChecks == 0) return ALL_SQUARES;
    
    if(maxChecks > 1) return 0;

    return lineOfAttack;
}