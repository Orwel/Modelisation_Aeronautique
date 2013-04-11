#ifndef FUSELAGE_H
#define FUSELAGE_H

#include "Scene.h"
#include "Volume.h"
#include "GravityCenter.h"

class Fuselage : public PieceManager
{
public:
    Fuselage(Scene &_scene,Volume _total,Volume _volume);
    virtual ~Fuselage();

    float getPositionFace(Relative face);

    void CalculateGravityCenter();
    Ogre::Vector3 getGravityCenter();

public:
    Scene &             scene;
    Ogre::SceneNode *   node;
    Ogre::ManualObject* manualObject;
    GravityCenter       gravityCenter;
    Volume              total;
    Volume              volume;
    arrayPoints         points;
    float               mass;
};

#endif // FUSELAGE_H
