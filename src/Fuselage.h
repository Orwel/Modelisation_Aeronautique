#ifndef FUSELAGE_H
#define FUSELAGE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Base.h"
#include "Scene.h"
#include "Volume.h"

#include <Memory>
#include <List>

typedef std::unique_ptr<Piece> PiecePtr;
typedef std::vector<PiecePtr> ListPiecePtr;

/////////////////////////////////////////////////
/// \brief Fuselage is main container for other pieces.
/// Fuselage can not move after creation.
/// Fuselage calculate it gravity center from it pieces
///
/////////////////////////////////////////////////
class Fuselage : public Base
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Fuselage(Scene &_scene,float mass,Volume _total,float thickness);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Fuselage();

    /** Manager list of piece */
    void AddPiece(Piece *piece);
    void DeletePiece(Piece *piece);
    void ClearPieces();

    /////////////////////////////////////////////////
    /// \brief Retourne la possition d'une des faces de la section du fuselage
    ///
    /// \param face Indique la face qui va retourner sa position
    /// \return Position de la face sur l'axe indiquer par la face
    ///
    /////////////////////////////////////////////////
    float getPositionFace(Relative face);

    /////////////////////////////////////////////////
    /// \brief Retourne la possition d'une des faces de la section du fuselage
    ///
    /// \param face Indique la face qui va retourner sa position
    /// \return Position de la face sur l'axe indiquer par la face
    ///
    /////////////////////////////////////////////////
    float getPositionFaceToPiece(Relative face);

    /////////////////////////////////////////////////
    /// \brief Calcule le centre de gravité du fuselage
    /// Le calcul prent en compte le fuselage et les piéces dans le fuselage
    ///
    /////////////////////////////////////////////////
    void CalculateGravityCenter();

    /////////////////////////////////////////////////
    /// \brief Retourne la mass du fuselage plus celle des piéces dedans
    ///
    /// \return la mass total du fuselage
    ///
    /////////////////////////////////////////////////
    inline float getMass(){return massTotal;}

public:
    Ogre::ManualObject* manualObject;           ///< Display object to fuselage's volume
    ListPiecePtr        pieces;                 ///w List piece in this section of fuselage
    Volume              total;                  ///< Volume total of fuselage
    Volume              volume;                 ///< Volume of container
    ArrayPoints         points;                 ///< Array of points to calculate gravity center
    float               massTotal;              ///< Mass of fuselage
};

#endif // FUSELAGE_H
