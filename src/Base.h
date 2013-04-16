#ifndef BASE_H
#define BASE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scene.h"
#include "Volume.h"

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
    Scene &             scene;
    Ogre::SceneNode *   node;
    Ogre::SceneNode *   nodeBox;
    Ogre::SceneNode *   nodeObject;
};

#endif // BASE_H
