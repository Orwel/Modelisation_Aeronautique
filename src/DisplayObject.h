#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre.h>
#include "Volume.h"

class DisplayObject
{
public:
    DisplayObject(Ogre::SceneManager *sceneManager);
    DisplayObject(Ogre::SceneManager *sceneManager,Ogre::SceneNode *parent);

    void BecomePavet(Volume volume, Ogre::ColourValue colour);
    void BecomePolygon3D(ArrayPoints &polygone,Ogre::ColourValue colour);

    /** Create with ManualObject */
    static Ogre::ManualObject* createPavet(Ogre::SceneManager *sceneManager,Volume volume, Ogre::ColourValue colour, const char * name=nullptr);
    static Ogre::ManualObject* createPolygon3D(Ogre::SceneManager *sceneManager,ArrayPoints &polygone,Ogre::ColourValue colour, const char * name=nullptr);

public:
    Ogre::SceneManager* sceneManager;       ///< Ref to scene manager
    Ogre::SceneNode*    node;               ///< Main node for display object
    Ogre::ManualObject* manualObject;       ///< Display object
};

#endif // DISPLAYOBJECT_H
