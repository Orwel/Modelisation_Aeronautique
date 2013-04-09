#include "Scene.h"
#include "Piece.h"


using namespace Ogre;

/*****************************************************************************/
Scene::Scene(Ogre::SceneManager *_sceneManager):sceneManager(_sceneManager)
{
    setLight();

    Piece piece1(*this,100.f,50.f,80.f,true);
    Piece piece2(*this,20.f,20.f,20.f);
    piece1.setPosition(70,80,50);
    piece2.PositionTo(piece1,Piece::POS_Z);
}

/*****************************************************************************/
Scene::~Scene()
{
    //dtor
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

ManualObject * Scene::createPavet(float weight, float heigth, float depth,const char * name)
{
    weight/=2;
    heigth/=2;
    depth/=2;
    ManualObject* manual;
    if(name == nullptr)
        manual = sceneManager->createManualObject();
    else
        manual = sceneManager->createManualObject(name);
    /*Devant*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(1,0,0,0.5);
    manual->position(-weight, -heigth, -depth);
    manual->position( weight, -heigth, -depth);
    manual->position( weight,  heigth, -depth);
    manual->position(-weight,  heigth, -depth);
    manual->position(-weight, -heigth, -depth);
    manual->end();
    /*Derriere*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(1,0,0,0.5);
    manual->position(-weight, -heigth, depth);
    manual->position( weight, -heigth, depth);
    manual->position( weight,  heigth, depth);
    manual->position(-weight,  heigth, depth);
    manual->position(-weight, -heigth, depth);
    manual->end();
    /*Droite*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(1,0,0,0.5);
    manual->position(weight, -heigth, -depth);
    manual->position(weight, -heigth, depth);
    manual->position(weight,  heigth, depth);
    manual->position(weight,  heigth, -depth);
    manual->position(weight, -heigth, -depth);
    manual->end();
    /*Gauche*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(1,0,0,0.5);
    manual->position(-weight, -heigth, -depth);
    manual->position(-weight, -heigth, depth);
    manual->position(-weight,  heigth, depth);
    manual->position(-weight,  heigth, -depth);
    manual->position(-weight, -heigth, -depth);
    manual->end();
    return manual;
}
