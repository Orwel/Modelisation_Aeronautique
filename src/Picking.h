#ifndef PICKING_H
#define PICKING_H

#include <Ogre.h>

class Piece;
class Fuselage;
class Scene;

class Picking
{
public:
    Picking(Ogre::SceneManager* sceneMgr);
    ~Picking();

    bool isPicked(Ogre::SceneNode *node1,Ogre::SceneNode *node2,float distance);

    static Piece* PickPiece(Scene& scene,Ogre::SceneManager* sceneMgr,Ogre::Ray ray);
    static Fuselage* PickSection(Scene& scene,Ogre::SceneManager* sceneMgr,Ogre::Ray ray);

private:
    Ogre::RaySceneQuery* mRayScnQuery; //!< Ray query
};

#endif // PICKING_H
