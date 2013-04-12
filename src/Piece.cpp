////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Piece.h"
#include "Fuselage.h"

using namespace Ogre;

/*****************************************************************************/
Piece::Piece(Scene& _scene,Fuselage& _fuselage,Volume _volume,Relative _stickFace):
    scene(_scene),fuselage(_fuselage),node(scene.sceneManager->getRootSceneNode()->createChildSceneNode()),
    gravityCenter(scene,node),volume(_volume),stickFace(_stickFace)
{
    fuselage.AddPiece(this);
    manualObject = scene.createPavet(volume,Ogre::ColourValue(0,0,1.f));
    node->attachObject(manualObject);
    MagnetismFuselage();
    DontLeaveFuselage();

    volume.addArrayPoint(points);
}

/*****************************************************************************/
Piece::~Piece()
{

}

/*****************************************************************************/
void Piece::Move(float axe1,float axe2)
{
    Vector3 move;
    if(stickFace == POS_X || stickFace == NEG_X )
        move = Vector3(0,axe1,axe2);
    else if(stickFace == POS_Y || stickFace == NEG_Y )
        move = Vector3(axe1,0,axe2);
    else if(stickFace == POS_Z || stickFace == NEG_Z )
        move = Vector3(axe1,axe2,0);

    node->translate(move);
    DontLeaveFuselage();
}

/*****************************************************************************/
void Piece::PositionTo(Relative face)
{
    stickFace = face;
    MagnetismFuselage();
    DontLeaveFuselage();
}

/*****************************************************************************/
void Piece::MagnetismFuselage()
{
    MagnetismFuselage(stickFace);
}

/*****************************************************************************/
void Piece::MagnetismFuselage(Relative face)
{
    Vector3 pos = node->getPosition();
    switch (face)
    {
    case POS_X:
        pos.x = -(volume.w/2) + fuselage.getPositionFace(face);
        break;
    case NEG_X:
        pos.x = volume.w/2 + fuselage.getPositionFace(face);
        break;
    case POS_Y:
        pos.y = -(volume.h/2) + fuselage.getPositionFace(face);
        break;
    case NEG_Y:
        pos.y = volume.h/2 + fuselage.getPositionFace(face);
        break;
    case POS_Z:
        pos.z = -(volume.d/2) + fuselage.getPositionFace(face);
        break;
    case NEG_Z:
        pos.z = volume.d/2 + fuselage.getPositionFace(face);
        break;
    }
    node->setPosition(pos);
}

void Piece::setPosition(float x,float y,float z)
{
    node->setPosition(x,y,z);
}

Ogre::Vector3 Piece::getPosition()
{
    return node->getPosition();
}

float Piece::getPositionFace(Relative face)
{
    return volume.getPositionFace(node->getPosition(),face);
}

/*****************************************************************************/
void Piece::DontLeaveFuselage()
{
    fuselage.getPositionFace(POS_X);
    getPositionFace(POS_X);
    if(getPositionFace(POS_X) > fuselage.getPositionFace(POS_X))
        MagnetismFuselage(POS_X);
    else if(getPositionFace(NEG_X) < fuselage.getPositionFace(NEG_X))
        MagnetismFuselage(NEG_X);

    if(getPositionFace(POS_Y) > fuselage.getPositionFace(POS_Y))
        MagnetismFuselage(POS_Y);
    else if(getPositionFace(NEG_Y) < fuselage.getPositionFace(NEG_Y))
        MagnetismFuselage(NEG_Y);

    if(getPositionFace(POS_Z) > fuselage.getPositionFace(POS_Z))
        MagnetismFuselage(POS_Z);
    else if(getPositionFace(NEG_Z) < fuselage.getPositionFace(NEG_Z))
        MagnetismFuselage(NEG_Z);
}

void Piece::CalculateGravityCenter()
{
    arrayPoints::iterator it;
    for(it=points.begin();it!=points.end();it++)
    {
        Ogre::Vector3 point = *it;
    }
    gravityCenter.setPosition(Vector3::ZERO);
}

Ogre::Vector3 Piece::getGravityCenter()
{
    return gravityCenter.getPosition();
}
