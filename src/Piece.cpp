////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Piece.h"
#include "Fuselage.h"

using namespace Ogre;

/*****************************************************************************/
Piece::Piece(Fuselage& _fuselage,float _mass,ArrayPoints &polygone,Ogre::Vector3 offset,Relative _stickFace):
    Base(_fuselage.scene),fuselage(_fuselage),gravityCenter(scene,node),stickFace(_stickFace),mass(_mass)
{
    fuselage.AddPiece(this);

    //Create point to piece
    offset /= 2.f;

    for(ArrayPoints::iterator it = polygone.begin();it != polygone.end();it++)
        points.push_back(Ogre::Vector3(*it+offset));
    for(ArrayPoints::iterator it = polygone.begin();it != polygone.end();it++)
        points.push_back(Ogre::Vector3(*it-offset));

    //Create Box
    volume = Volume(points);
    manualBox = scene.createPavet(volume,Ogre::ColourValue::Blue);
    nodeBox->attachObject(manualBox);
    //Create shape
    manualObject = scene.createPolygon3D(points,Ogre::ColourValue::Blue);
    nodeObject->attachObject(manualObject);


    MagnetismFuselage();
    DontLeaveFuselage();
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

/*****************************************************************************/
void Piece::CalculateGravityCenter()
{
    Ogre::Vector3 bary = GravityCenter::averagePoints(points);
    gravityCenter.setPosition(bary);
}

/*****************************************************************************/
Ogre::Vector3 Piece::getGravityCenter()
{
    return gravityCenter.getPosition();
}
