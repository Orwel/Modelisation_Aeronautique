#ifndef GRAVITYCENTER_H
#define GRAVITYCENTER_H

#include <Ogre.h>

class Scene;

class GravityCenter
{
public:
    GravityCenter(Scene& _scene, Ogre::SceneNode * parent=nullptr);
    ~GravityCenter();

    void setParentSceneNode(Ogre::SceneNode * parent);

    Ogre::Vector3 getPosition();
    void setPosition(Ogre::Vector3 position);

private:
    void CreateGravityObject();

private:
    Scene&              scene;
    Ogre::SceneNode *   node;
    Ogre::ManualObject* manualObject;
};

#endif // GRAVITYCENTER_H
