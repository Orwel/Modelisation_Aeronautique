#ifndef FUSELAGE_H
#define FUSELAGE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scene.h"
#include "Volume.h"
#include "GravityCenter.h"

/////////////////////////////////////////////////
/// \brief Fuselage is main container for other pieces.
/// Fuselage can not move after creation.
/// Fuselage calculate it gravity center from it pieces
///
/////////////////////////////////////////////////
class Fuselage : public PieceManager
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Fuselage(Scene &_scene,Volume _total,Volume _volume);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Fuselage();

    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param face Indique la face qui va retourner sa position
    /// \return Position de la face sur l'axe indiquer par la face
    ///
    /////////////////////////////////////////////////
    float getPositionFace(Relative face);

    /////////////////////////////////////////////////
    /// \brief Calcule le centre de gravit� du fuselage
    /// Le calcul prent en compte le fuselage et les pi�ces dans le fuselage
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

public:
    Scene &             scene;                  ///< Ref to scene
    Ogre::SceneNode *   node;                   ///< Main node of fuselage
    Ogre::ManualObject* manualObject;           ///< Display object to fuselage's volume
    GravityCenter       gravityCenter;          ///< Gravity center of fuselage
    Volume              total;                  ///< Volume total of fuselage
    Volume              volume;                 ///< Volume of container
    arrayPoints         points;                 ///< Array of points to calculate gravity center
    float               mass;                   ///< Mass of fuselage
};

#endif // FUSELAGE_H
