////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Fuselage.h"
#include "Piece.h"
#include "DisplayObject.h"
#include "ColourConstant.h"

/*****************************************************************************/
Fuselage::Fuselage(Scene &_scene,float _mass,Volume _total,float thickness):Base(_scene,mass),
    total(_total),volume(total.w-thickness,total.h-thickness,total.d-thickness),massTotal(1)
{
    scene.AddFuselage(this);
    box.BecomePavet(volume,ColourConstant::fuselageBox);
    CreateGravityObject();
    volume.addArrayPoint(points);
}

/*****************************************************************************/
Fuselage::~Fuselage()
{

}

/*****************************************************************************/
void Fuselage::AddPiece(Piece *piece)
{
    pieces.push_back(PiecePtr(piece));
}

/*****************************************************************************/
void Fuselage::DeletePiece(Piece *piece)
{
    ListPiecePtr::iterator it;
    for(it = pieces.begin() ; it!=pieces.end() ; it++)
    {
        if(it->get()== piece)
        {
            pieces.erase(it);
            return;
        }
    }
}

/*****************************************************************************/
void Fuselage::ClearPieces()
{
    pieces.clear();
}

/*****************************************************************************/
float Fuselage::getPositionFace(Relative face)
{
    return volume.getPositionFace(node->getPosition(),face);
}

/*****************************************************************************/
float Fuselage::getPositionFaceToPiece(Relative face)
{
    return volume.getPositionFace(face);
}

/*****************************************************************************/
void Fuselage::CalculateGravityCenter()
{
    Ogre::Vector3 bary = Ogre::Vector3::ZERO;
    massTotal=0;

    /* Calcul des pieces du fuselage */
    ListPiecePtr::iterator it;
    for(it = pieces.begin() ; it!=pieces.end() ; it++)
    {
        Piece& piece = *(*it);
        bary+= piece.getGravityCenterMorePosition() * piece.getMass();
        massTotal += piece.getMass();
    }

    /* Calcul de la section du fuselage */
    Ogre::Vector3 baryF = Volume::averagePoints(points);
    bary += baryF * this->mass;
    massTotal += this->mass;

    if(massTotal>0)
        bary = bary / massTotal;
    else
        bary = Ogre::Vector3::ZERO;
    gravityCenter.setPosition(bary);
}
