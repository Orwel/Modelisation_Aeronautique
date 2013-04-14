////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scene.h"
#include "Piece.h"
#include "Fuselage.h"
#include "LoaderXML.h"

using namespace Ogre;

/*****************************************************************************/
Scene::Scene(Ogre::SceneManager *_sceneManager):sceneManager(_sceneManager),selected(nullptr),gravityCenter(*this)
{
    setLight();

    LoaderXML::LoadModel(*this,"Model1.xml");
    //Fuselage * fuselage = new Fuselage(*this,3,Volume(110.f,60.f,90.f),5);
    //Piece * piece2 = new Piece(*this,*fuselage,Volume(20.f,20.f,20.f),POS_Z);
    //selected = piece2;
    CalculateGravityCenter();
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
ManualObject * Scene::createPavet(Volume volume, Ogre::ColourValue colour,const char * name)
{
    volume.w/=2;
    volume.h/=2;
    volume.d/=2;
    ManualObject* manual;
    if(name == nullptr)
        manual = sceneManager->createManualObject();
    else
        manual = sceneManager->createManualObject(name);
    /*Devant*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->position( volume.w, -volume.h, -volume.d);
    manual->position( volume.w,  volume.h, -volume.d);
    manual->position(-volume.w,  volume.h, -volume.d);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->end();
    /*Derriere*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(-volume.w, -volume.h, volume.d);
    manual->position( volume.w, -volume.h, volume.d);
    manual->position( volume.w,  volume.h, volume.d);
    manual->position(-volume.w,  volume.h, volume.d);
    manual->position(-volume.w, -volume.h, volume.d);
    manual->end();
    /*Droite*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(volume.w, -volume.h, -volume.d);
    manual->position(volume.w, -volume.h, volume.d);
    manual->position(volume.w,  volume.h, volume.d);
    manual->position(volume.w,  volume.h, -volume.d);
    manual->position(volume.w, -volume.h, -volume.d);
    manual->end();
    /*Gauche*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->position(-volume.w, -volume.h, volume.d);
    manual->position(-volume.w,  volume.h, volume.d);
    manual->position(-volume.w,  volume.h, -volume.d);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->end();
    return manual;
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

void Scene::CalculateGravityCenter()
{
    Ogre::Vector3 bary = Ogre::Vector3::ZERO;
    float massTotal=0;

    /* Calcul des pieces du fuselage */
    ListFuselagePtr::iterator it;
    for(it = sections.begin() ; it!=sections.end() ; it++)
    {
        Fuselage& section = *(*it);
        bary+= section.getGravityCenter() * section.getMass();
        massTotal += section.getMass();
    }

    if(massTotal>0)
        bary = bary / massTotal;
    else
        bary = Ogre::Vector3::ZERO;
    gravityCenter.setPosition(bary);
}
