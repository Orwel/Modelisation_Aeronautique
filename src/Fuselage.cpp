////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Fuselage.h"

/*****************************************************************************/
Fuselage::Fuselage(Scene &_scene,Volume _total,Volume _volume):scene(_scene),
    node(scene.sceneManager->getRootSceneNode()->createChildSceneNode()),gravityCenter(scene,node),total(_total),volume(_volume)
{
    manualObject = scene.createPavet(volume,Ogre::ColourValue(1.f,0,0));
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

/*****************************************************************************/
void Fuselage::CalculateGravityCenter()
{
    {
        ListPiecePtr::iterator it;
        for(it = pieces.begin() ; it!=pieces.end() ; it++)
        {
            Piece& piece = *(*it);

        }
    }

    {
        arrayPoints::iterator it;
        for(it=points.begin();it!=points.end();it++)
        {
            Ogre::Vector3 point = *it;
        }
    }

    gravityCenter.setPosition(Ogre::Vector3::ZERO);
}

/*****************************************************************************/
Ogre::Vector3 Fuselage::getGravityCenter()
{
    return gravityCenter.getPosition();
}
