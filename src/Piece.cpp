#include "Piece.h"

using namespace Ogre;

/*****************************************************************************/
Piece::Piece(Scene &_scene,float _weight,float _heigth,float _depth,bool _fuselage):scene(_scene),
    weight(_weight),heigth(_heigth),depth(_depth),fuselage(_fuselage)
{
    manualObject = scene.createPavet(_weight,_heigth,_depth);
    node = scene.sceneManager->getRootSceneNode()->createChildSceneNode();
    node->attachObject(manualObject);
}

/*****************************************************************************/
Piece::~Piece()
{
    //dtor
}

/*****************************************************************************/
void Piece::PositionTo(Piece &piece,Relative face)
{
    Magnetism(piece, face);
    if(piece.fuselage)
        DontLeaveFuselage(piece);
}

/*****************************************************************************/
void Piece::Magnetism(Piece &piece,Relative face)
{
    Vector3 pos = node->getPosition();
    switch (face)
    {
    case POS_X:
        pos.x = -(weight/2) + piece.getPositionFace(face);
        break;
    case NEG_X:
        pos.x = weight/2 + piece.getPositionFace(face);
        break;
    case POS_Y:
        pos.y = -(heigth/2) + piece.getPositionFace(face);
        break;
    case NEG_Y:
        pos.y = heigth/2 + piece.getPositionFace(face);
        break;
    case POS_Z:
        pos.z = -(depth/2) + piece.getPositionFace(face);
        break;
    case NEG_Z:
        pos.z = depth/2 + piece.getPositionFace(face);
        break;
    }
    node->setPosition(pos);
}

void Piece::setPosition(float x,float y,float z)
{
    node->setPosition(x,y,z);
}

float Piece::getPositionFace(Relative face)
{
    switch (face)
    {
    case POS_X:
        return weight/2 + node->getPosition().x;
    case NEG_X:
        return -weight/2 + node->getPosition().x;
    case POS_Y:
        return heigth/2 + node->getPosition().y;
    case NEG_Y:
        return -heigth/2 + node->getPosition().y;
    case POS_Z:
        return depth/2 + node->getPosition().z;
    case NEG_Z:
        return -depth/2 + node->getPosition().z;
    }
    return 0.f;
}

void Piece::DontLeaveFuselage(Piece &fuselage)
{
    if(getPositionFace(POS_X) > fuselage.getPositionFace(POS_X))
        Magnetism(fuselage, POS_X);
    else if(getPositionFace(NEG_X) < fuselage.getPositionFace(NEG_X))
        Magnetism(fuselage, NEG_X);

    if(getPositionFace(POS_Y) > fuselage.getPositionFace(POS_Y))
        Magnetism(fuselage, POS_Y);
    else if(getPositionFace(NEG_Y) < fuselage.getPositionFace(NEG_Y))
        Magnetism(fuselage, NEG_Y);

    if(getPositionFace(POS_Z) > fuselage.getPositionFace(POS_Z))
        Magnetism(fuselage, POS_Z);
    else if(getPositionFace(NEG_Z) < fuselage.getPositionFace(NEG_Z))
        Magnetism(fuselage, NEG_Z);
}
