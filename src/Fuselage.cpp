////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Fuselage.h"
#include "Piece.h"

/*****************************************************************************/
Fuselage::Fuselage(Scene &_scene,Volume _total,Volume _volume):scene(_scene),
    node(scene.sceneManager->getRootSceneNode()->createChildSceneNode()),gravityCenter(scene,node),total(_total),volume(_volume)
{
    manualObject = scene.createPavet(volume,Ogre::ColourValue(1.f,0,0));
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
    massTotal += piece->getMass();
}

/*****************************************************************************/
void Fuselage::DeletePiece(Piece *piece)
{
    ListPiecePtr::iterator it;
    for(it = pieces.begin() ; it!=pieces.end() ; it++)
    {
        if(it->get()==piece)
        {
            massTotal -= piece->getMass();
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

    Ogre::Vector3 bary= Ogre::Vector3::ZERO;
    massTotal=0;
    {
        ListPiecePtr::iterator it;

        for(it = pieces.begin() ; it!=pieces.end() ; it++)
        {
            Piece& piece = *(*it);
            bary+= piece.getGravityCenter() * piece.getMass();
            massTotal += piece.getMass();
        }
    }

    {
        Ogre::Vector3 baryF = Ogre::Vector3::ZERO;
        arrayPoints::iterator it;
        for(it=points.begin();it!=points.end();it++)
        {
            Ogre::Vector3 point = *it;
            baryF += point;
        }
        baryF = baryF / points.size();
        bary += baryF * this->mass;
        massTotal += this->mass;
    }
    std::cout<<"step step5"<<std::endl;
    if(massTotal>0)
        bary = bary / massTotal;
    else
        bary = Ogre::Vector3::ZERO;
    std::cout<<"step step6"<<std::endl;
    gravityCenter.setPosition(bary);
}

/*****************************************************************************/
Ogre::Vector3 Fuselage::getGravityCenter()
{
    return gravityCenter.getPosition();
}
