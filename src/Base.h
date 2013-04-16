#ifndef BASE_H
#define BASE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scene.h"

class Base
{
public:
    Base(Scene& _scene);
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
    /// \brief Return position of piece
    ///
    /// \return position of piece
    ///
    /////////////////////////////////////////////////
    Ogre::Vector3 getPosition();


public:
    Scene &             scene;          ///< Ref to scene
    Ogre::SceneNode *   node;           ///< Main node
    Ogre::SceneNode *   nodeBox;        ///< Box' node
    Ogre::SceneNode *   nodeObject;     ///< Object' node
};

#endif // BASE_H
