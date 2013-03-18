
/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial2.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial2_h_
#define __BasicTutorial2_h_

#include "BaseApplication.h"
#include "OrbitCamera.h"

class BasicTutorial2 : public BaseApplication
{
public:
    BasicTutorial2(void);
    virtual ~BasicTutorial2(void);

    OrbitCamera * orbitalCamera;
    Ogre::SceneNode *nNinja;
protected:
    virtual void createScene(void);
    virtual void createCamera(void);
    virtual void createViewports(void);
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
};

#endif // #ifndef __BasicTutorial2_h_
