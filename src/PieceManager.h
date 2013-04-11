#ifndef PIECEMANAGER_H
#define PIECEMANAGER_H

#include <list>

class Piece;

class PieceManager
{
public:
    PieceManager();
    ~PieceManager();

    void AddPiece(Piece *piece);
    void DeletePiece(Piece *piece);
    void ClearPiece();

protected:
    typedef std::list<Piece*> ListPiecePtr;
    ListPiecePtr pieces; ///< list of piece

    friend class Piece;
};

#endif // PIECEMANAGER_H
