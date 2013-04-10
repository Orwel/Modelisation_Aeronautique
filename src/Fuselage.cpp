#include "Fuselage.h"

/*****************************************************************************/
Fuselage::Fuselage(Scene &_scene,Volume _total,Volume _volume):scene(_scene),total(_total),volume(_volume)
{
    manualObject = scene.createPavet(volume);
    node = scene.sceneManager->getRootSceneNode()->createChildSceneNode();
    node->attachObject(manualObject);
}

/*****************************************************************************/
Fuselage::~Fuselage()
{

}

/*****************************************************************************/
float Fuselage::getPositionFace(Relative face)
{
    return volume.getPositionFace(node->getPosition(),face);
}
