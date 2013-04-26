////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Piece.h"
#include "Fuselage.h"
#include "DisplayObject.h"
#include "ColourConstant.h"

using namespace Ogre;

/*****************************************************************************/
Piece::Piece(Fuselage& _fuselage,float _mass,ArrayPoints &polygone,Ogre::Vector3 offset,Relative _stickFace,Ogre::Vector3 position):
    Base(_fuselage.scene,Base::PIECE,_fuselage.node,_mass),fuselage(_fuselage),stickFace(_stickFace)
{
    fuselage.AddPiece(this);

    //Create point to piece
    Ogre::Vector3 min,max,offpos;
    Volume::MinMaxFromPoints(polygone,min,max);
    offset /= 2.f;
    offpos = -(min+max)/2.f;

    for(ArrayPoints::iterator it = polygone.begin();it != polygone.end();it++)
        points.push_back(Ogre::Vector3(*it+offpos+offset));
    for(ArrayPoints::iterator it = polygone.begin();it != polygone.end();it++)
        points.push_back(Ogre::Vector3(*it+offpos-offset));

    //Create Box
    volume = Volume(points);
    box.BecomePavet(volume,ColourConstant::pieceBox);
    //Create shape
    object.BecomePolygon3D(points,ColourConstant::piece);
    //Create Gravity center
    CreateGravityObject();

    Base::setPosition(position);
    //CorrectCollission();
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
void Piece::setPosition(Ogre::Vector3 position)
{
    Base::setPosition(position);
    MagnetismFuselage();
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
    case NONE:
        break;
    case POS_X:
        pos.x = -(volume.w/2) + fuselage.getPositionFaceToPiece(face);
        break;
    case NEG_X:
        pos.x = volume.w/2 + fuselage.getPositionFaceToPiece(face);
        break;
    case POS_Y:
        pos.y = -(volume.h/2) + fuselage.getPositionFaceToPiece(face);
        break;
    case NEG_Y:
        pos.y = volume.h/2 + fuselage.getPositionFaceToPiece(face);
        break;
    case POS_Z:
        pos.z = -(volume.d/2) + fuselage.getPositionFaceToPiece(face);
        break;
    case NEG_Z:
        pos.z = volume.d/2 + fuselage.getPositionFaceToPiece(face);
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
    if(getPositionFace(POS_X) > fuselage.getPositionFaceToPiece(POS_X))
        MagnetismFuselage(POS_X);
    else if(getPositionFace(NEG_X) < fuselage.getPositionFaceToPiece(NEG_X))
        MagnetismFuselage(NEG_X);

    if(getPositionFace(POS_Y) > fuselage.getPositionFaceToPiece(POS_Y))
        MagnetismFuselage(POS_Y);
    else if(getPositionFace(NEG_Y) < fuselage.getPositionFaceToPiece(NEG_Y))
        MagnetismFuselage(NEG_Y);

    if(getPositionFace(POS_Z) > fuselage.getPositionFaceToPiece(POS_Z))
        MagnetismFuselage(POS_Z);
    else if(getPositionFace(NEG_Z) < fuselage.getPositionFaceToPiece(NEG_Z))
        MagnetismFuselage(NEG_Z);
}

/*****************************************************************************/
void Piece::CorrectCollission()
{
    Ogre::Vector3 intersection;
    bool make = false;
    for(const auto &piece:fuselage.pieces)
    {
        make |= Volume::boxCollide(volume,getPosition(),piece->volume,piece->getPosition(),intersection);
    }

    if(make)
    {
        Ogre::Vector3 absIntersection(std::abs(intersection.x),std::abs(intersection.y),std::abs(intersection.z));
        if(absIntersection.x>absIntersection.y && absIntersection.x>absIntersection.z)
            intersection = Ogre::Vector3(intersection.x,0,0);
        else if(absIntersection.y>absIntersection.x && absIntersection.y>absIntersection.z)
            intersection = Ogre::Vector3(0,intersection.y,0);
        else if(absIntersection.z>absIntersection.x && absIntersection.z>absIntersection.y)
            intersection = Ogre::Vector3(0,0,intersection.z);
        node->translate(intersection);
        DontLeaveFuselage();
    }
}

/*****************************************************************************/
void Piece::CalculateGravityCenter()
{
    Ogre::Vector3 bary = Volume::averagePoints(points);
    gravityCenter.setPosition(bary);
}

/*****************************************************************************/
void Piece::Display()
{
    std::cout<<"Gravity center "<<getGravityCenter()<<"  Position "<<getPosition()<<"   Mass "<<mass<<std::endl;
}
