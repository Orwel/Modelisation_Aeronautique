#ifndef BASE_H
#define BASE_H

#include "Scene.h"
#include "Volume.h"

class Base
{
public:
    Base(Scene& _scene,Volume _volume);
    ~Base();

public:
    Scene &             scene;
    Ogre::SceneNode *   node;
    Ogre::ManualObject* manualObject;
    Volume              volume;
};

#endif // BASE_H
