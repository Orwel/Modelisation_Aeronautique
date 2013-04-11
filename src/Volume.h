#ifndef VOLUME_H
#define VOLUME_H

#include <Ogre.h>

enum Relative
{
    POS_X,
    POS_Y,
    POS_Z,
    NEG_X,
    NEG_Y,
    NEG_Z
};

class Volume
{
public:


public:
    Volume();
    Volume(float weight,float heigth,float depth);
    virtual ~Volume();

    float getPositionFace(Relative face);
    float getPositionFace(Ogre::Vector3 pos,Relative face);
public:

    float w;        /** Weight */
    float h;        /** Heigth */
    float d;        /** Depth */

};

#endif // VOLUME_H
