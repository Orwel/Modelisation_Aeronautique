////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Application.h"

/*****************************************************************************/
Application::Application():mRoot(0), mWindow(0), mSceneMgr(0), nCamera(0)
{

}

/*****************************************************************************/
Application::~Application()
{
    OGRE_DELETE mRoot;
}

/*****************************************************************************/
bool Application::Initialize ()
{
#ifdef _DEBUG
    Ogre::String pluginFile = "plugins_d.cfg";
#else
    Ogre::String pluginFile = "plugins.cfg";
#endif

    // on créée le noeud root de la scène
    mRoot = OGRE_NEW
            Root(pluginFile);
    // on charge les objets
    ConfigFile configFile;
    configFile.load("resources.cfg");
    ConfigFile::SectionIterator seci = configFile.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
    // récupération des config de l'utilisateur
    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    {
        return false;
    }


    initScene();
    inputListener = new InputListener(scene,mSceneMgr,mWindow,orbitalCamera);
    mRoot->addFrameListener(inputListener);

    return true;
}

/*****************************************************************************/
void Application::initScene ()
{
    // on crée la fenêtre
    mWindow = mRoot->initialise(true, "Short Story");
    // on charge les ressources pour de vrai
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // on crée le scene manager
    mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "Scene Manager");
    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    // on crée la caméra
    nCamera = mSceneMgr->getRootSceneNode()->createChildSceneNode("camera");
    orbitalCamera = new OrbitCamera(mSceneMgr,nCamera);
    camera = orbitalCamera->getCamera();
    if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
    {
        camera->setFarClipDistance(0);   // enable infinite far clip distance if we can
    }
    else
    {
        camera->setFarClipDistance(2000);
    }

    Viewport* vp = mWindow->addViewport(camera);
    vp->setBackgroundColour(ColourValue(0, 0, 0));
    camera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

    scene = new Scene(mSceneMgr);
}

/*****************************************************************************/
bool Application::start ()
{
    bool continu = true;

    while (continu)
    {
        WindowEventUtilities::messagePump();

        if (mWindow->isClosed())
            continu = false;

        if (!mRoot->renderOneFrame())
            continu = false;
    }
    return continu;
}
