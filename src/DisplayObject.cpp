////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "DisplayObject.h"

using namespace Ogre;

/*****************************************************************************/
DisplayObject::DisplayObject(SceneManager *_sceneManager):sceneManager(_sceneManager),
    node(sceneManager->getRootSceneNode()->createChildSceneNode()),manualObject(nullptr)
{

}

/*****************************************************************************/
DisplayObject::DisplayObject(SceneManager *_sceneManager,SceneNode *parent):sceneManager(_sceneManager),
    node(parent->createChildSceneNode()),manualObject(nullptr)
{

}

/*****************************************************************************/
void DisplayObject::BecomePavet(Volume volume, Ogre::ColourValue colour)
{
    if(manualObject)
        sceneManager->destroyManualObject(manualObject);
    manualObject = createPavet(sceneManager,volume,colour);
    node->attachObject(manualObject);
}

/*****************************************************************************/
void DisplayObject::BecomePolygon3D(ArrayPoints &polygone,Ogre::ColourValue colour)
{
    if(manualObject)
        sceneManager->destroyManualObject(manualObject);
    manualObject = createPolygon3D(sceneManager,polygone,colour);
    node->attachObject(manualObject);
}


/*****************************************************************************/
ManualObject * DisplayObject::createPavet(SceneManager *sceneManager,Volume volume, ColourValue colour,const char * name)
{
    volume.w/=2;
    volume.h/=2;
    volume.d/=2;
    ManualObject* manual;
    if(name == nullptr)
        manual = sceneManager->createManualObject();
    else
        manual = sceneManager->createManualObject(name);
    /*Devant*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->position( volume.w, -volume.h, -volume.d);
    manual->position( volume.w,  volume.h, -volume.d);
    manual->position(-volume.w,  volume.h, -volume.d);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->end();
    /*Derriere*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(-volume.w, -volume.h, volume.d);
    manual->position( volume.w, -volume.h, volume.d);
    manual->position( volume.w,  volume.h, volume.d);
    manual->position(-volume.w,  volume.h, volume.d);
    manual->position(-volume.w, -volume.h, volume.d);
    manual->end();
    /*Droite*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(volume.w, -volume.h, -volume.d);
    manual->position(volume.w, -volume.h, volume.d);
    manual->position(volume.w,  volume.h, volume.d);
    manual->position(volume.w,  volume.h, -volume.d);
    manual->position(volume.w, -volume.h, -volume.d);
    manual->end();
    /*Gauche*/
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->position(-volume.w, -volume.h, volume.d);
    manual->position(-volume.w,  volume.h, volume.d);
    manual->position(-volume.w,  volume.h, -volume.d);
    manual->position(-volume.w, -volume.h, -volume.d);
    manual->end();
    return manual;
}

ManualObject* DisplayObject::createPolygon3D(SceneManager *sceneManager,ArrayPoints &polygone, ColourValue colour,const char * name)
{
    unsigned int halfSize = polygone.size()/2;
    ManualObject* manual;
    if(name == nullptr)
        manual = sceneManager->createManualObject();
    else
        manual = sceneManager->createManualObject(name);
    /** Face 1 */
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    for(unsigned int i=0; i<halfSize; i++)
    {
        manual->position(polygone[i]);
    }
    manual->position(polygone[0]);
    manual->end();
    /** Face 2 */
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    for(unsigned int i=halfSize; i<polygone.size(); i++)
    {
        manual->position(polygone[i]);
    }
    manual->position(polygone[halfSize]);
    manual->end();
    /** Face what link face1 and face2 */
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
    manual->colour(colour);
    manual->position(polygone[0]);
    manual->position(polygone[halfSize-1]);
    manual->position(polygone[polygone.size()-1]);
    manual->position(polygone[halfSize]);
    manual->position(polygone[0]);
    manual->end();

    for(unsigned i = 0; i < halfSize-1; i++)
    {
        manual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
        manual->colour(colour);
        manual->position(polygone[i]);
        manual->position(polygone[i+1]);
        manual->position(polygone[i+halfSize+1]);
        manual->position(polygone[i+halfSize]);
        manual->position(polygone[i]);
        manual->end();
    }


    return manual;
}
