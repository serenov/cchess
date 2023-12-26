#include "interface.h"
#include "magicBoards.h"
#include <stdlib.h>
#include <stdio.h>



extern Boards __boards__;

#define BUFFER_LENGTH 5
#define MIN_LENGTH 4

#ifdef _WIN32
    // Windows
    #define CLEAR_SCREEN() system("cls")
#else
    // Unix-like systems
    #define CLEAR_SCREEN() printf("\033[H\033[2J")
#endif

void initBuffer(char *buffer)
{
    for(int i = 0; i < BUFFER_LENGTH; i++) buffer[i] = 0;
    
}

inline static bool getBufferAndValidateLength(char *buffer)
{
    int count = 0;
    char c;
    while((c = getchar()) != '\n')
    {
        if(count >= BUFFER_LENGTH) return false;
        buffer[count++] = c;
    }

    if(count < (MIN_LENGTH - 1)) return false;

    return true;
}

InterfaceInformation getInputAndValidate(char *buffer)
{
    if(!getBufferAndValidateLength(buffer))
    {
        return lengthError;
    } 

    for(int i = 0; i < 4; i++)
    {
        char currentChar = *(buffer++);
        if(i % 2) 
        {
            // ODD
            if(currentChar < '1' || currentChar > '8') 
            {
                return RankError;
            }
        }
        else 
        {
            // EVEN
            if(currentChar < 'a' || currentChar > 'h')
            {
                return FileError;
            }
        }
    }

    // if(*buffer != 0 && *buffer != '\n') {
    //     if(buffer)
    // }
    return allFine;
}

InterfaceInformation decodeAndPlay(char *input)
{
    // input must be 5 characters long
    
    Square from = input[0] - 'a' + (input[1] - '1') * 8;
    Square to = input[2] - 'a' + (input[3] - '1') * 8;

    if(!playMoveOnBoards(from, to, input[4]))
    {
        return illegalMoveError;
    }
    return allFine;
}





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

void printInterfaceInformation(InterfaceInformation is)
{
    switch (is)
    {
    case allFine:
        char *s = __boards__.state[__boards__.movesCount].colorToPlay == white? "white": "black";
        printf("[INFO] Now %s's turn.", s);
        break;
    case RankError:
        printf("[ERROR] Invalid rank.");
        break;
    case FileError:
        printf("[ERROR] Invalid rank input.");
        break;
    case illegalMoveError:
        printf("[ERROR] Illegal move.");
        break;
    
    default:
        break;
    }
}

void gameloop()
{
    char buffer[BUFFER_LENGTH];

    GameStatus gs;
    InterfaceInformation is = allFine;

    // clearing for the first render
    CLEAR_SCREEN();
    

    while((gs = getGameStatus()) == RUNNING)
    {
        printInterfaceInformation(is); 
        displayBoard();
        initBuffer(buffer);

        if((is = getInputAndValidate(buffer)) == allFine)
        {
            is = decodeAndPlay(buffer);
        }

        CLEAR_SCREEN();
    }
}



int main(int argc, char *argv)
{
    initMagicBoards(); 
    setFEN(NULL);

    gameloop();

    // displayBitboard(__boards__.bitboards.blackKing);
    // displayBitboard(__boards__.bitboards.whiteKing);
    // displayBitboard(__boards__.bitboards.occupiedBoard);
    // displayBitboard(__boards__.bitboards.whitePieces);
    // displayBitboard(__boards__.bitboards.blackPieces);
    // displayBitboard(__boards__.bitboards.occupiedRotated90LBoard);
    // displayBitboard(__boards__.bitboards.occupiedRotated45LBoard);
    // displayBitboard(__boards__.bitboards.occupiedRotated45RBoard);

    return 0;
}