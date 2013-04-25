////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scene.h"
#include "Piece.h"
#include "Fuselage.h"
#include "LoaderXML.h"
#include "SaverXML.h"
#include "ColourConstant.h"

using namespace Ogre;

/*****************************************************************************/
Scene::Scene(Ogre::SceneManager *_sceneManager):sceneManager(_sceneManager),selected(nullptr),gravityCenter(sceneManager),
    gravityBalance(sceneManager)
{
    setLight();
    LoadModel(*this,"Model2.xml");
    gravityCenter.BecomePavet(Volume(0.5,0.5,0.5),ColourConstant::gravityCenterModel);
    gravityBalance.BecomePavet(Volume(10,10,10),ColourConstant::balanceGravity);
    CalculateGravityCenter();
    SaveModel(*this,"sqdfgdsq.xml");
}

/*****************************************************************************/
Scene::~Scene()
{

}

/*****************************************************************************/
void Scene::AddFuselage(Fuselage *fuselage)
{
    sections.push_back(FuselagePtr(fuselage));
}

/*****************************************************************************/
void Scene::DeleteFuselage(Fuselage *fuselage)
{
    ListFuselagePtr::iterator it;
    for(it = sections.begin() ; it!=sections.end() ; it++)
    {
        if(it->get()== fuselage)
        {
            sections.erase(it);
            return;
        }
    }
}

/*****************************************************************************/
void Scene::ClearFuselages()
{
    sections.clear();
}

/*****************************************************************************/
void Scene::setLight()
{
    sceneManager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
    sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    Ogre::Light* pointLight = sceneManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 250));
    pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight->setSpecularColour(1.0, 0.0, 0.0);

    Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));

    Ogre::Light* spotLight = sceneManager->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setDirection(-1, -1, 0);
    spotLight->setPosition(Ogre::Vector3(300, 300, 0));
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
}

/*****************************************************************************/
void Scene::moveSelectedPiece(float x,float y,float z)
{
    if(selected)
        selected->Move(x,y);
}

/*****************************************************************************/
bool Scene::isPieceSelected()
{
    if(selected)
        return true;
    return false;
}

/*****************************************************************************/
void Scene::setMagnetism(Relative face)
{
    if(selected)
        selected->PositionTo(face);
}

/*****************************************************************************/
void Scene::setVisiblePiecesBox(bool visible)
{
    for(ListFuselagePtr::iterator itF = sections.begin();itF != sections.end();itF++)
    {
        for(ListPiecePtr::iterator itP = (*itF)->pieces.begin();itP != (*itF)->pieces.end();itP++)
        {
            (*itP)->setVisibleBox(visible);
        }
    }
}

/*****************************************************************************/
void Scene::CalculateGravityCenter()
{
    Ogre::Vector3 bary = Ogre::Vector3::ZERO;
    float massTotal=0;

    /* Calcul des pieces du fuselage */
    ListFuselagePtr::iterator it;
    for(it = sections.begin() ; it!=sections.end() ; it++)
    {
        Fuselage& section = *(*it);
        section.CalculateGravityCenter();
        bary+= section.getGravityCenterMorePosition() * section.getMass();
        massTotal += section.getMass();
    }

    if(massTotal>0)
        bary = bary / massTotal;
    else
        bary = Ogre::Vector3::ZERO;
    gravityCenter.setPosition(bary);
}

/*****************************************************************************/
void Scene::DisplayGravityCenterAllEntity()
{
    std::cout<<"DisplayGravityCenterAllEntity"<<std::endl;
    int countSection=0;
    for(ListFuselagePtr::iterator itF = sections.begin();itF != sections.end();itF++)
    {
        int countPiece=0;
        for(ListPiecePtr::iterator itP = (*itF)->pieces.begin();itP != (*itF)->pieces.end();itP++)
        {
            std::cout<<"Piece "<<++countPiece<<std::endl;
            (*itP)->Display();
        }
        std::cout<<"Section "<<++countSection<<" : "<<(*itF)->getGravityCenter()<<std::endl;
    }
    std::cout<<"Model : "<<gravityCenter.getPosition()<<std::endl;
}
