#ifndef PIECE_H
#define PIECE_H

#include "Scene.h"

class Piece
{
public:
    enum Relative
    {
        POS_X,
        POS_Y,
        POS_Z,
        NEG_X,
        NEG_Y,
        NEG_Z
    };

public:
    Piece(Scene &_scene,float _weight,float _heigth,float _depth,bool _fuselage=false);
    virtual ~Piece();

    void setPosition(float x,float y,float z);

    float getPositionFace(Relative face);

    void PositionTo(Piece &piece,Relative face);

    void Magnetism(Piece &piece,Relative face);

    void DontLeaveFuselage(Piece &fuselage);

private:
    Scene &             scene;
    Ogre::SceneNode *   node;
    Ogre::ManualObject* manualObject;
    float               weight;
    float               heigth;
    float               depth;
    bool                fuselage;
};

#endif // PIECE_H
