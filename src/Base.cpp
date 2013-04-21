////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Base.h"

/*****************************************************************************/
Base::Base(Scene& _scene):scene(_scene),node(scene.sceneManager->getRootSceneNode()->createChildSceneNode()),
        box(scene.sceneManager,node),object(scene.sceneManager,node)
{

}

/*****************************************************************************/
Base::Base(Scene& _scene,Ogre::SceneNode *parent):scene(_scene),node(parent->createChildSceneNode()),
        box(scene.sceneManager,node),object(scene.sceneManager,node)
{

}

/*****************************************************************************/
Base::~Base()
{
    scene.sceneManager->destroySceneNode(node);
}

/*****************************************************************************/
void Base::setPosition(float x,float y,float z)
{
    node->setPosition(x,y,z);
}

/*****************************************************************************/
void Base::setPosition(Ogre::Vector3 position)
{
    node->setPosition(position);
}

/*****************************************************************************/
Ogre::Vector3 Base::getPosition()
{
    return node->getPosition();
}
