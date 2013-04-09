#ifndef SCENE_H
#define SCENE_H

#include <Ogre.h>

/**
*   Cet objet manipule l'ensemble des objets contenu dans la scene
*/
class Scene
{
public:
    /** Constructor */
    Scene(Ogre::SceneManager *_sceneManager);
    /** Destructor */
    ~Scene();

    /** Create with ManualObject */
    Ogre::ManualObject * createPavet(float weight, float heigth, float depth, const char * name=nullptr);

private:
    /** Lumieres */
    void setLight();

public:
    /** Le scene manager */
    Ogre::SceneManager * sceneManager;
    /** Noeud indiquant le centre du monde */
    Ogre::SceneNode* nCenter;
    /** Noeud parent des elements du modele */
    Ogre::SceneNode* nPattern;
};

#endif // SCENE_H
