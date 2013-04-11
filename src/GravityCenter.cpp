#include "GravityCenter.h"
#include "Scene.h"

GravityCenter::GravityCenter(Scene &_scene,Ogre::SceneNode * parent):scene(_scene)
{
    CreateGravityObject();
    if(parent)
        node = parent->createChildSceneNode();
    else
        node = scene.sceneManager->getRootSceneNode()->createChildSceneNode();
    node->attachObject(manualObject);

}

GravityCenter::~GravityCenter()
{

}

void GravityCenter::setParentSceneNode(Ogre::SceneNode * parent)
{
    node->getParentSceneNode()->removeChild(node);;
    parent->addChild(node);
}

void GravityCenter::CreateGravityObject()
{
    manualObject = scene.createPavet(Volume(0.5,0.5,0.5),Ogre::ColourValue(0,1.f,0));
}

Ogre::Vector3 GravityCenter::getPosition()
{
    return node->getPosition();
}

void GravityCenter::setPosition(Ogre::Vector3 position)
{
    node->setPosition(position);
}
