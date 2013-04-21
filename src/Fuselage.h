#ifndef FUSELAGE_H
#define FUSELAGE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Base.h"
#include "Scene.h"
#include "Volume.h"
#include "GravityCenter.h"

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
    /// \brief Retourne la position du centre de gravite
    ///
    /// \return La position du centre de gravite
    ///
    /////////////////////////////////////////////////
    Ogre::Vector3 getGravityCenter();

    /////////////////////////////////////////////////
    /// \brief Retourne la mass de la piece
    ///
    /// \return La mass de la piece
    ///
    /////////////////////////////////////////////////
    inline float getMass(){return massTotal;}

public:
    Ogre::ManualObject* manualObject;           ///< Display object to fuselage's volume
    ListPiecePtr        pieces;
    GravityCenter       gravityCenter;          ///< Gravity center of fuselage
    Volume              total;                  ///< Volume total of fuselage
    Volume              volume;                 ///< Volume of container
    ArrayPoints         points;                 ///< Array of points to calculate gravity center
    float               mass;                   ///< Mass of fuselage
    float               massTotal;              ///< Mass of fuselage
};

#endif // FUSELAGE_H
