#ifndef PIECE_H
#define PIECE_H

#include "Scene.h"
#include "Volume.h"

class Fuselage;

class Piece
{
public:
    Piece(Scene& _scene,Fuselage& _fuselage,Volume _volume,Relative _stickFace);
    virtual ~Piece();

    float getPositionFace(Relative face);

    void setPosition(float x,float y,float z);

    Ogre::Vector3 getPosition();

    void Move(float axe1,float axe2);

    void PositionTo(Relative face);

    void MagnetismFuselage();
    void MagnetismFuselage(Relative face);

    void DontLeaveFuselage();

private:
    /** La scene contenant les objets a manipuler */
    Scene &             scene;
    Fuselage &          fuselage;
    Ogre::SceneNode *   node;
    Ogre::ManualObject* manualObject;
    Volume              volume;
    Relative            stickFace;
};

#endif // PIECE_H
