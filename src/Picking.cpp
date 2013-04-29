#include "Picking.h"
#include "Scene.h"
#include "Piece.h"
#include "Fuselage.h"

Picking::Picking(Ogre::SceneManager* sceneMgr)
{
    mRayScnQuery = sceneMgr->createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
    mRayScnQuery->setSortByDistance(true);
}

Picking::~Picking()
{
    //dtor
}

Piece* Picking::PickPiece(Scene& scene,Ogre::SceneManager* sceneMgr,Ogre::Ray ray)
{
    //Create query
    Ogre::RaySceneQuery* mRayScnQuery = sceneMgr->createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
    mRayScnQuery->setSortByDistance(true);
    mRayScnQuery->setRay(ray);

    //Send ray
    Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr;

    //Discover result
    for (itr = result.begin(); itr!=result.end(); itr++)
    {
        if(itr->movable)
        {
            Ogre::Node* node = itr->movable->getParentNode();
            for(auto& section:scene.sections)
            {
                for(auto& piece:section->pieces)
                {
                    if(piece->box.node == node)
                        return piece.get();
                }
            }
        }
    }
    return nullptr;
}

Fuselage* Picking::PickSection(Scene& scene,Ogre::SceneManager* sceneMgr,Ogre::Ray ray)
{
    //Create query
    Ogre::RaySceneQuery* mRayScnQuery = sceneMgr->createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
    mRayScnQuery->setSortByDistance(true);
    mRayScnQuery->setRay(ray);

    //Send ray
    Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr;

    //Discover result
    for (itr = result.begin(); itr!=result.end(); itr++)
    {
        if(itr->movable)
        {
            Ogre::Node* node = itr->movable->getParentNode();
            for(auto& section:scene.sections)
            {
                if(section->box.node == node)
                    return section.get();
            }
        }
    }
    return nullptr;
}
