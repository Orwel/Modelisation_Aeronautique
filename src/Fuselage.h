#ifndef FUSELAGE_H
#define FUSELAGE_H

#include "Scene.h"
#include "Volume.h"

class Fuselage : public PieceManager
{
public:
    Fuselage(Scene &_scene,Volume _total,Volume _volume);
    virtual ~Fuselage();

    float getPositionFace(Relative face);

public:
    Scene &             scene;
    Ogre::SceneNode *   node;
    Ogre::ManualObject* manualObject;
    Volume              total;
    Volume              volume;
};

#endif // FUSELAGE_H
