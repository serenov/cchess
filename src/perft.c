#include "engine.h"
#include <stdio.h>
#include <stdlib.h>

extern Boards __boards__;

void displayBoard()
{
    for (int y = 7; y > -1; y--)
    {

        printf("\n -------------------------------\n");
        for (int x = 0; x < 8; x++)
        {
            printf("| %c ", __boards__.board[y * 8 + x]);
        }
        printf("|");
    }
    printf("\n -------------------------------\n");

    // displayBitboard(__boards__.bitboards.occupiedBoard);
    // displayBitboard(__boards__.bitboards.whitePieces);
    // displayBitboard(__boards__.bitboards.blackPieces);
    // displayBitboard(__boards__.bitboards.occupiedRotated90LBoard);
    // displayBitboard(__boards__.bitboards.occupiedRotated45LBoard);
    // displayBitboard(__boards__.bitboards.occupiedRotated45RBoard);
}

const Piece pieceIterationArray[][6] = {
    {
        blackKing,
        blackQueen,
        blackRook,
        blackBishop,
        blackKnight,
        blackPawn,
    },
    {
        whiteKing,
        whiteQueen,
        whiteRook,
        whiteBishop,
        whiteKnight,
        whitePawn,
    }
};


int movecnt = 0;
int enpassantCnt = 0;

void perftTest(int depth) {
    if (depth < 1) return;

    GameStatus status = getGameStatus();

    if (status == STALEMATE || status == CHECKMATE)
    {
        return;
    }

    Color clr = getColor(true);

    for (int i = 0; i < 6; i++) {
        Piece currentPiece = pieceIterationArray[clr][i];
        
        Bitboard tempBitboard = *(getBitboardForPiece(currentPiece));

        while(tempBitboard != 0) {
            int fromPosition  = ctz(tempBitboard);

            Bitboard legalMoves = getLegalMovesForSquare(fromPosition);
            displayBitboard(legalMoves);

            if(depth == 1) movecnt += __builtin_popcountll(legalMoves);

            while(legalMoves != 0) {

                int toPosition = ctz(legalMoves);

                playMoveOnBoards(fromPosition, toPosition, ' ');

                printf("from: %d, to: %d\n", fromPosition, toPosition);
                displayBoard();


                MoveType mvtype = __boards__.state[__boards__.movesCount].typeOfMove;

                if(mvtype == EnpassantMove) {
                    displayBoard();
                    enpassantCnt++;
                }

                // displayBoard();

                perftTest(depth - 1);

                undoLastMove();

                legalMoves &= ~(1UL << toPosition);
            }

            tempBitboard &= ~(1UL << fromPosition);
        }
    }
}

int main() {

    initMagicBoards(); 

    if(!setFEN(NULL)) {
        printf("Improper FEN.");
        exit(1);
    };

    perftTest(2);

    printf("%d %d\n", movecnt, enpassantCnt);


    return 1;
}