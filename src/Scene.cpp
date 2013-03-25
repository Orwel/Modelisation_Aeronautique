#include "Scene.h"

/*****************************************************************************/
Scene::Scene(Ogre::SceneManager *_sceneManager):sceneManager(_sceneManager)
{
    setLight();
    //Cube test
    Ogre::Entity* entCube = sceneManager->createEntity("Cube",Ogre::SceneManager::PT_CUBE);
    Ogre::SceneNode* nCube = sceneManager->getRootSceneNode()->createChildSceneNode("Cube");
    nCube->attachObject(entCube);
    nCube->setScale(2,1,10);

    Ogre::Entity* entCube2 = sceneManager->createEntity("Cube2",Ogre::SceneManager::PT_CUBE);
    Ogre::SceneNode* nCube2 = sceneManager->getRootSceneNode()->createChildSceneNode("Cube2");
    nCube2->attachObject(entCube2);
    nCube2->setScale(10,2,2);
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
