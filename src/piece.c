#include "piece.h"

extern Boards __boards__;

Color getColorByPiece(Piece p)
{

    if(p == nullPiece) return noColor;

    if(p > WHITE_BOUNDARY) return black;

    return white;
}

Piece getPieceByName(PieceName name, bool isFriendly)
{
    // relative to the turns of the players


    Color requestedColor = getColor(isFriendly);

    switch (name)
    {
    case King:
        if(requestedColor == black) return blackKing;
        return whiteKing;
    case Queen:
        if(requestedColor == black) return blackQueen;
        return whiteQueen;
    case Bishop:
        if(requestedColor == black) return blackBishop;
        return whiteBishop;
    case Rook:
        if(requestedColor == black) return blackRook;
        return whiteRook;
    case Knight:
        if(requestedColor == black) return blackKnight;
        return whiteKnight;
    case Pawn:
        if(requestedColor == black) return blackPawn;
        return whitePawn;
    }

    return nullPiece;
}

Piece getPieceByColor(PieceName name, Color clr)
{
    switch (name)
    {
    case King:
        if(clr == black) return blackKing;
        return whiteKing;
    case Queen:
        if(clr == black) return blackQueen;
        return whiteQueen;
    case Bishop:
        if(clr == black) return blackBishop;
        return whiteBishop;
    case Rook:
        if(clr == black) return blackRook;
        return whiteRook;
    case Knight:
        if(clr == black) return blackKnight;
        return whiteKnight;
    case Pawn:
        if(clr == black) return blackPawn;
        return whitePawn;
    }  

    return nullPiece;
}

Color getColor(bool isFriendly) 
{
    Color currentPlayingColor = __boards__.state[__boards__.movesCount].colorToPlay;

    return (isFriendly)? currentPlayingColor: !currentPlayingColor;
}
