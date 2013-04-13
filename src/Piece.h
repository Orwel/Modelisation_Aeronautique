#ifndef PIECE_H
#define PIECE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scene.h"
#include "Volume.h"
#include "GravityCenter.h"

class Fuselage;
class InputListener;

/////////////////////////////////////////////////
/// \brief
///
///
/////////////////////////////////////////////////
class Piece
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Piece(Scene& _scene,Fuselage& _fuselage,Volume _volume,Relative _stickFace);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Piece();


    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param face Indique la face qui va retourner sa position
    /// \return Position de la face sur l'axe indiquer par la face
    ///
    /////////////////////////////////////////////////
    float getPositionFace(Relative face);


    /////////////////////////////////////////////////
    /// \brief Set position to piece
    ///
    /// \param x
    /// \param y
    /// \param z
    ///
    /////////////////////////////////////////////////
    void setPosition(float x,float y,float z);

    /////////////////////////////////////////////////
    /// \brief Return position of piece
    ///
    /// \return position of piece
    ///
    /////////////////////////////////////////////////
    Ogre::Vector3 getPosition();

    /////////////////////////////////////////////////
    /// \brief Move position of piece
    ///
    /// \param axe1
    /// \param axe2
    ///
    /////////////////////////////////////////////////
    void Move(float axe1,float axe2);

    /////////////////////////////////////////////////
    /// \brief Change face what magnetism piece
    ///
    /// \param face what will magnetism piece
    ///
    /////////////////////////////////////////////////
    void PositionTo(Relative face);

    /////////////////////////////////////////////////
    /// \brief Stick piece on fuselage's face select by PositionTo
    ///
    /////////////////////////////////////////////////
    void MagnetismFuselage();

    /////////////////////////////////////////////////
    /// \brief Stick piece on fuselage's face select by parameter
    ///
    /// \param face select face who will magnetism the piece
    ///
    /////////////////////////////////////////////////
    void MagnetismFuselage(Relative face);

    /////////////////////////////////////////////////
    /// \brief Check and correct if piece is out of fuselage
    ///
    /////////////////////////////////////////////////
    void DontLeaveFuselage();

    /////////////////////////////////////////////////
    /// \brief Calcule le centre de gravité de la piece
    /// Le calcul utilise les points comme reference
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
    inline float getMass(){return mass;}

private:
    Scene &             scene;              ///< Ref to scene
    Fuselage &          fuselage;           ///< Ref to parent fuselage
    Ogre::SceneNode *   node;               ///< Main node of piece
    Ogre::ManualObject* manualObject;       ///< Display object to fuselage's volume
    GravityCenter       gravityCenter;      ///< Gravity center of piece
    float               mass;               ///< Mass of fuselage
    Volume              volume;             ///< Volume of piece
    Relative            stickFace;          ///< Select face what magnetism the piece

    arrayPoints         points;             ///< Shape of piece

    friend InputListener;
};

#endif // PIECE_H
