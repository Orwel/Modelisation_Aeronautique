#include "PieceManager.h"
#include "Piece.h"

/*****************************************************************************/
PieceManager::PieceManager()
{
    //ctor
}

/*****************************************************************************/
PieceManager::~PieceManager()
{
    ClearPiece();
}

/*****************************************************************************/
void PieceManager::AddPiece(Piece *piece)
{
    pieces.push_back(piece);
}

/*****************************************************************************/
void PieceManager::DeletePiece(Piece *piece)
{
    std::list<Piece*>::iterator it = std::find(pieces.begin(),pieces.end(),piece);
    if(it!=pieces.end())
    {
        delete *it;
        pieces.erase(it);
    }
}

/*****************************************************************************/
void PieceManager::ClearPiece()
{
    std::list<Piece*>::iterator it;
    for(it = pieces.begin(); it!=pieces.end(); it++)
    {
        delete *it;
    }
    pieces.clear();
}
