////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "OrbitCamera.h"

OrbitCamera::OrbitCamera(Ogre::SceneManager *sceneMgr, Ogre::SceneNode *target)
{
    this->sceneMgr = sceneMgr;
    this->targetNode = target;

    this->orbiting = false;
    this->zooming = false;

    // create the camera
    this->camera = this->sceneMgr->createCamera("orbitCam");
    this->camera->setNearClipDistance(1);
    this->camera->setFarClipDistance(1000);

    // enable infinite far clip distance if we can
    if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
        this->camera->setFarClipDistance(0);

    // set the position ant rotation of the camera to look at the target
    this->camera->setPosition(this->targetNode->_getDerivedPosition());
    this->camera->setOrientation(this->targetNode->_getDerivedOrientation());
    this->camera->yaw(Ogre::Radian(180));
    this->camera->pitch(Ogre::Radian(-15));
    this->camera->moveRelative(Ogre::Vector3(0, 0, 20));

    // set the camera to track itself the target and don't 'roll' rotate
    this->camera->setAutoTracking(true, this->targetNode);
    this->camera->setFixedYawAxis(true);
}

OrbitCamera::~OrbitCamera()
{
    this->sceneMgr->destroyCamera("orbitCam");
}

void OrbitCamera::updateMovement(const OIS::MouseEvent &evt)
{
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();

    if (this->orbiting)   // yaw around the target, and pitch locally
    {
        updateOrbitingMovement(evt.state.X.rel,evt.state.Y.rel,evt.state.Z.rel);
    }
    else if (this->zooming)  // move the camera toward or away from the target
    {
        updateOrbitingMovement(evt.state.Y.rel);
    }
    else if (evt.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        if((-evt.state.Z.rel > 0 && dist < 400) ||
                (-evt.state.Z.rel < 0 && dist > 10))
            this->camera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.0008f * dist));
    }

}

void OrbitCamera::updateOrbitingMovement(float x_rel,float y_rel,float z_rel)
{
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    this->camera->setPosition(this->targetNode->_getDerivedPosition());
    this->camera->yaw(Ogre::Degree(-x_rel * 0.25f));
    this->camera->pitch(Ogre::Degree(-y_rel * 0.25f));
    this->camera->moveRelative(Ogre::Vector3(0, 0, dist));
}

void OrbitCamera::updateOrbitingMovement(float rel)
{
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    this->camera->moveRelative(Ogre::Vector3(0, 0, -rel * 0.004f * dist));
}

Ogre::Camera *OrbitCamera::getCamera(void)
{
    return this->camera;
}

bool OrbitCamera::getOrbiting(void)
{
    return this->orbiting;
}

void OrbitCamera::setOrbiting(bool orbiting)
{
    this->orbiting = orbiting;
}

bool OrbitCamera::getZooming(void)
{
    return this->zooming;
}

void OrbitCamera::setZooming(bool zooming)
{
    this->zooming = zooming;
}

void OrbitCamera::setTarget(Ogre::SceneNode * target)
{
    targetNode = target;
}

Ogre::Ray OrbitCamera::getRay()
{
    return Ogre::Ray(camera->getPosition(),camera->getDirection());
}
