////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Base.h"

/*****************************************************************************/
Base::Base(Scene& _scene):scene(_scene),node(scene.sceneManager->getRootSceneNode()->createChildSceneNode()),
        nodeBox(node->createChildSceneNode()),nodeObject(node->createChildSceneNode())
{

}

/*****************************************************************************/
Base::~Base()
{

}

/*****************************************************************************/
void Base::setPosition(float x,float y,float z)
{
    node->setPosition(x,y,z);
}

/*****************************************************************************/
Ogre::Vector3 Base::getPosition()
{
    return node->getPosition();
}
