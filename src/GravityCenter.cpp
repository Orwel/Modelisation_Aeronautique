////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "GravityCenter.h"
#include "Scene.h"
#include "DisplayObject.h"

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
    manualObject = DisplayObject::createPavet(scene.sceneManager,Volume(0.5,0.5,0.5),Ogre::ColourValue::Green);
}

Ogre::Vector3 GravityCenter::getPosition()
{
    return node->getPosition();
}

void GravityCenter::setPosition(Ogre::Vector3 position)
{
    node->setPosition(position);
}

Ogre::Vector3 GravityCenter::averagePoints(ArrayPoints points)
{
        Ogre::Vector3 bary = Ogre::Vector3::ZERO;
        if(points.size() > 0)
        {
            ArrayPoints::iterator it;
            for(it=points.begin();it!=points.end();it++)
            {
                Ogre::Vector3 point = *it;
                bary += point;
            }
            bary = bary / points.size();
        }
        return bary;
}
