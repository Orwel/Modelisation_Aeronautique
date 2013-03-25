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

private:
    /** Lumieres */
    void setLight();

private:
    /** Le scene manager */
    Ogre::SceneManager *sceneManager;

public:
    /** Noeud indiquant le centre du monde */
    Ogre::SceneNode* nCenter;
    /** Noeud parent des elements du modele */
    Ogre::SceneNode* nPattern;
};

#endif // SCENE_H
