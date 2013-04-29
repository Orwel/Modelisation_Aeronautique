////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "InputListener.h"
#include "Piece.h"

/*****************************************************************************/
InputListener::InputListener(Scene *_scene,SceneManager* _sceneManager,RenderWindow* _window,OrbitCamera* _orbitCamera):
    scene(_scene),sceneManager(_sceneManager),windows(_window),orbitCamera(_orbitCamera),modeInput(NONE)
{
    startOIS();
    mContinuer = true;
    zooningOrbitalCamera = false;
}

/*****************************************************************************/
InputListener::~InputListener ()
{
    WindowEventUtilities::removeWindowEventListener(windows, this);
    windowClosed(windows);
}

/*****************************************************************************/
void InputListener::startOIS ()
{
    LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    LogManager::getSingletonPtr()->logMessage("*** Step 1 ***");
    windows->getCustomAttribute("GXLWINDOW", &windowHnd);
    LogManager::getSingletonPtr()->logMessage("*** Step 3 ***");
    windowHndStr << windowHnd;
    LogManager::getSingletonPtr()->logMessage("*** Step 4 ***");
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    LogManager::getSingletonPtr()->logMessage("*** Step 5 ***");

    inputManager = InputManager::createInputSystem(pl);
    mMouse = static_cast<Mouse*>(inputManager->createInputObject(OISMouse, true));
    mKeyboard = static_cast<Keyboard*>(inputManager->createInputObject(OISKeyboard, true));

    windowResized(windows);
    WindowEventUtilities::addWindowEventListener(windows, this);
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
}

/*****************************************************************************/
bool InputListener::frameRenderingQueued (const FrameEvent& evt)
{
    if (windows->isClosed())
        return false;

    mKeyboard->capture();
    mMouse->capture();

    return mContinuer;
}

/*****************************************************************************/
void InputListener::windowResized (RenderWindow* wnd)
{
    unsigned int width, height, depth;
    int left, top;
    wnd->getMetrics(width, height, depth, left, top);

    const MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

/*****************************************************************************/
void InputListener::windowClosed (RenderWindow* wnd)
{
    if (wnd == windows)
    {

    }
}

/*****************************************************************************/
bool InputListener::mouseMoved (const MouseEvent &e)
{
    switch(modeInput)
    {
    case NONE:
        break;
    case MODE_CAMERA:
        orbitCamera->updateMovement(e);
        break;
    case MODE_MOVE_PIECE:
        scene->moveSelectedPiece(e.state.X.rel,e.state.Y.rel,e.state.Z.rel);
        break;
    }
    return true;
}

/*****************************************************************************/
bool InputListener::mousePressed (const MouseEvent &arg, MouseButtonID id)
{
    if (id == OIS::MB_Right)
    {
        LogManager::getSingletonPtr()->logMessage("*** test ***");
        modeInput = MODE_CAMERA;
        orbitCamera->setOrbiting(!zooningOrbitalCamera);
        orbitCamera->setZooming(zooningOrbitalCamera);
    }
    return true;
}

/*****************************************************************************/
bool InputListener::mouseReleased (const MouseEvent &arg, MouseButtonID id)
{
    if (id == OIS::MB_Right)
    {
        if(scene->isPieceSelected())
            modeInput = MODE_MOVE_PIECE;
        else
            modeInput = NONE;
        orbitCamera->setOrbiting(false);
        orbitCamera->setZooming(false);
    }
    return true;
}

/*****************************************************************************/
bool InputListener::keyPressed (const KeyEvent &e)
{
    switch (e.key)
    {
    case OIS::KC_ESCAPE:
        mContinuer = false;
        break;
    case OIS::KC_W:
        zooningOrbitalCamera = !zooningOrbitalCamera;
        break;
    case OIS::KC_U:
        scene->setMagnetism(POS_X);
        break;
    case OIS::KC_J:
        scene->setMagnetism(NEG_X);
        break;
    case OIS::KC_I:
        scene->setMagnetism(POS_Y);
        break;
    case OIS::KC_K:
        scene->setMagnetism(NEG_Y);
        break;
    case OIS::KC_O:
        scene->setMagnetism(POS_Z);
        break;
    case OIS::KC_L:
        scene->setMagnetism(NEG_Z);
        break;
    case OIS::KC_B:
        scene->ClearFuselages();
        break;
    case OIS::KC_N:
        scene->DisplayGravityCenterAllEntity();
        break;
    default:
        break;
    }
    return mContinuer;
}

/*****************************************************************************/
bool InputListener::keyReleased (const KeyEvent &e)
{
    return true;
}
