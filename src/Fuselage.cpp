////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Fuselage.h"
#include "Piece.h"

/*****************************************************************************/
Fuselage::Fuselage(Scene &_scene,float _mass,Volume _total,float thickness):scene(_scene),
    node(scene.sceneManager->getRootSceneNode()->createChildSceneNode()),gravityCenter(scene,node),
    total(_total),volume(total.w-thickness,total.h-thickness,total.d-thickness),mass(_mass),massTotal(1)
{
    scene.AddFuselage(this);
    manualObject = scene.createPavet(volume,Ogre::ColourValue::Red);
    node->attachObject(manualObject);
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
    //massTotal += piece->getMass();
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
void Fuselage::CalculateGravityCenter()
{
    Ogre::Vector3 bary = Ogre::Vector3::ZERO;
    massTotal=0;

    /* Calcul des pieces du fuselage */
    ListPiecePtr::iterator it;
    for(it = pieces.begin() ; it!=pieces.end() ; it++)
    {
        Piece& piece = *(*it);
        bary+= piece.getGravityCenter() * piece.getMass();
        massTotal += piece.getMass();
    }

    /* Calcul de la section du fuselage */
    Ogre::Vector3 baryF = GravityCenter::averagePoints(points);
    bary += baryF * this->mass;
    massTotal += this->mass;

    if(massTotal>0)
        bary = bary / massTotal;
    else
        bary = Ogre::Vector3::ZERO;
    gravityCenter.setPosition(bary);
}

/*****************************************************************************/
Ogre::Vector3 Fuselage::getGravityCenter()
{
    return gravityCenter.getPosition();
}
