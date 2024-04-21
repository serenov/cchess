#include "magicBoardConstants.h"
#include "magicBoards.h"
#include <stdio.h>
int main()
{
    initMagicBoards();


    for(int i = 0; i < 64; i++) 
    {
        for(int j = 0; j < 256; j++)
        {
            displayBitboard(__attackRightDiagonal__[i][j]);
            // displayBitboard(__attackLeftDiagonal__[i][j]);
        }
    } 
    // for(int i = 0; i < 64; i++) displayBitboard(__pawnAttack__[0][i]);
    // for(int i = 0; i < 8; i++) displayBitboard(__ranks__[i]);
    // for(int i = 0; i < 8; i++) displayBitboard(__files__[i]);

    return 0;
}