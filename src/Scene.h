#ifndef SCENE_H
#define SCENE_H

#include <Ogre.h>

class Scene
{
public:
    Scene(Ogre::SceneManager *_sceneManager);
    virtual ~Scene();

private:
    void setLight();

private:
    Ogre::SceneManager *sceneManager;

public:
    Ogre::SceneNode* nCenter;
    Ogre::SceneNode* nPattern;
};

#endif // SCENE_H
