#ifndef BASE_H
#define BASE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scene.h"
#include "DisplayObject.h"

class Base
{
public:

    enum Type
    {
        PIECE,
        FUSELAGE
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Base(Scene& _scene,Type type,float _mass = 1.f);

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor with scene node parent
    ///
    ////////////////////////////////////////////////////////////
    Base(Scene& _scene,Type type,Ogre::SceneNode *parent,float _mass = 1.f);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Base();

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
    /// \brief Set position to piece
    ///
    /// \param x
    /// \param y
    /// \param z
    ///
    /////////////////////////////////////////////////
    void setPosition(Ogre::Vector3 position);

    /////////////////////////////////////////////////
    /// \brief Return position of piece
    ///
    /// \return position of piece
    ///
    /////////////////////////////////////////////////
    Ogre::Vector3 getPosition();

    /////////////////////////////////////////////////
    /// \brief Retourne la position du centre de gravite
    ///
    /// \return La position du centre de gravite
    ///
    /////////////////////////////////////////////////
    Ogre::Vector3 getGravityCenter();

    /////////////////////////////////////////////////
    /// \brief Retourne la position du centre de gravite plus la position du noeud
    ///
    /// \return la position du centre de gravite plus la position du noeud
    ///
    /////////////////////////////////////////////////
    Ogre::Vector3 getGravityCenterMorePosition();

    /////////////////////////////////////////////////
    /// \brief set if box is display or no
    ///
    /// \param box true if box is displayed
    ///
    /////////////////////////////////////////////////
    void setVisibleBox(bool visible);

    /////////////////////////////////////////////////
    /// \brief Créer les objets à afficher pour representer le centre de gravite
    ///
    /////////////////////////////////////////////////
    void CreateGravityObject();

    /////////////////////////////////////////////////
    /// \brief Return mass
    ///
    /// \return mass value
    ///
    /////////////////////////////////////////////////
    inline float getMass(){return mass;}

public:
    Scene &             scene;          ///< Ref to scene
    Ogre::SceneNode *   node;           ///< Main node
    DisplayObject       box;            ///< Box
    DisplayObject       object;         ///< Displayed object
    DisplayObject       gravityCenter;  ///< Gravity center of piece
    float               mass;           ///< Mass of object
    Type                type;
};

#endif // BASE_H
