#include "appwidget.h"

const QPoint     AppWidget::invalidMousePoint(-1,-1);
const Ogre::Real AppWidget::turboModifier(10);

AppWidget::AppWidget(QWidget *parent) :
    QWidget(parent) ,
    mRoot(0), mWindow(0), mSceneMgr(0), nCamera(0) ,ogreViewport(0),
    oldPos(invalidMousePoint)
{
    setAttribute(Qt::WA_OpaquePaintEvent,true);
    setAttribute(Qt::WA_PaintOnScreen,true);
    //setMinimumSize(120,120);
    setFocusPolicy(Qt::ClickFocus);
}

/*****************************************************************************/
AppWidget::~AppWidget()
{
    if(mWindow)
    {
        mWindow->removeAllViewports();
    }

    if(mRoot)
    {
        mRoot->detachRenderTarget(mWindow);

        if(mSceneMgr)
        {
            mRoot->destroySceneManager(mSceneMgr);
        }
    }

    delete mRoot;
}

/*****************************************************************************/
bool AppWidget::Initialize ()
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
void AppWidget::initScene ()
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

void AppWidget::setBackgroundColor(QColor c)
{
    if(ogreViewport)
    {
        Ogre::ColourValue ogreColour;
        ogreColour.setAsARGB(c.rgba());
        ogreViewport->setBackgroundColour(ogreColour);
    }
}

/*****************************************************************************/

void AppWidget::setCameraPosition(const Ogre::Vector3 &pos)
{
    camera->setPosition(pos);
    camera->lookAt(0,50,0);
    update();
    emit cameraPositionChanged(pos);
}

/*****************************************************************************/

void AppWidget::keyPressEvent(QKeyEvent *e)
{
        static QMap<int, Ogre::Vector3> keyCoordModificationMapping;
        static bool mappingInitialised = false;

        if(!mappingInitialised)
        {
                keyCoordModificationMapping[Qt::Key_W] 		  = Ogre::Vector3( 0, 0,-5);
                keyCoordModificationMapping[Qt::Key_S] 		  = Ogre::Vector3( 0, 0, 5);
                keyCoordModificationMapping[Qt::Key_A] 		  = Ogre::Vector3(-5, 0, 0);
                keyCoordModificationMapping[Qt::Key_D] 		  = Ogre::Vector3( 5, 0, 0);
                keyCoordModificationMapping[Qt::Key_PageUp]   = Ogre::Vector3( 0, 5, 0);
                keyCoordModificationMapping[Qt::Key_PageDown] = Ogre::Vector3( 0,-5, 0);

                mappingInitialised = true;
        }

        QMap<int, Ogre::Vector3>::iterator keyPressed =
                keyCoordModificationMapping.find(e->key());
        if(keyPressed != keyCoordModificationMapping.end() && camera)
        {
                const Ogre::Vector3 &actualCamPos = camera->getPosition();
                setCameraPosition(actualCamPos + keyPressed.value());

                e->accept();
        }
    else
    {
        e->ignore();
    }
}

/*****************************************************************************/

void AppWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        Ogre::Real x = e->pos().x() / (float)width();
        Ogre::Real y = e->pos().y() / (float)height();

        Ogre::Ray ray = camera->getCameraToViewportRay(x, y);
        Ogre::RaySceneQuery *query = mSceneMgr->createRayQuery(ray);
        Ogre::RaySceneQueryResult &queryResult = query->execute();
        Ogre::RaySceneQueryResult::iterator queryResultIterator = queryResult.begin();

        if(queryResultIterator != queryResult.end())
        {
            if(queryResultIterator->movable)
            {
                nCamera = queryResultIterator->movable->getParentSceneNode();
                nCamera->showBoundingBox(true);
            }
        }
        else
        {
            nCamera->showBoundingBox(false);
            nCamera = 0;
        }

        mSceneMgr->destroyQuery(query);

        update();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

/*****************************************************************************/

void AppWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton) && oldPos != invalidMousePoint)
    {
        const QPoint &pos = e->pos();
        Ogre::Real deltaX = pos.x() - oldPos.x();
        Ogre::Real deltaY = pos.y() - oldPos.y();

        if(e->modifiers().testFlag(Qt::ControlModifier))
        {
            deltaX *= turboModifier;
            deltaY *= turboModifier;
        }

        Ogre::Vector3 camTranslation(deltaX, deltaY, 0);
        const Ogre::Vector3 &actualCamPos = camera->getPosition();
        setCameraPosition(actualCamPos + camTranslation);

        oldPos = pos;
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

/*****************************************************************************/

void AppWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = e->pos();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

/*****************************************************************************/

void AppWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(!e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = QPoint(invalidMousePoint);
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

/*****************************************************************************/

void AppWidget::moveEvent(QMoveEvent *e)
{
    QWidget::moveEvent(e);

    if(e->isAccepted() && mWindow)
    {
        mWindow->windowMovedOrResized();
        update();
    }
}

/*****************************************************************************/

QPaintEngine* AppWidget::paintEngine() const
{
    // We don't want another paint engine to get in the way for our Ogre based paint engine.
    // So we return nothing.
    return NULL;
}

/*****************************************************************************/

void AppWidget::paintEvent(QPaintEvent *e)
{
    mRoot->_fireFrameStarted();
        mWindow->update();
    mRoot->_fireFrameEnded();

    e->accept();
}

/*****************************************************************************/

void AppWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    if(e->isAccepted())
    {
        const QSize &newSize = e->size();
        if(mWindow)
        {
            mWindow->resize(newSize.width(), newSize.height());
            mWindow->windowMovedOrResized();
        }
        if(camera)
        {
            Ogre::Real aspectRatio = Ogre::Real(newSize.width()) / Ogre::Real(newSize.height());
            camera->setAspectRatio(aspectRatio);
        }
    }
}

/*****************************************************************************/

void AppWidget::showEvent(QShowEvent *e)
{
    if(!mRoot)
    {
        //initOgreSystem();
        Initialize();
    }

    QWidget::showEvent(e);
}

/*****************************************************************************/

void AppWidget::wheelEvent(QWheelEvent *e)
{
    Ogre::Vector3 zTranslation(0,0, -e->delta() / 60);

    if(e->modifiers().testFlag(Qt::ControlModifier))
    {
        zTranslation.z *= turboModifier;
    }

    const Ogre::Vector3 &actualCamPos = camera->getPosition();
    setCameraPosition(actualCamPos + zTranslation);

    e->accept();
}

/*****************************************************************************/
/*
void AppWidget::initOgreSystem()
{
    mRoot = new Ogre::Root();

    Ogre::RenderSystem *renderSystem = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
    mRoot->setRenderSystem(renderSystem);
    mRoot->initialise(false);

    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

    Ogre::NameValuePairList viewConfig;
    Ogre::String widgetHandle;
#ifdef Q_WS_WIN
    widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
#else
    QWidget *q_parent = dynamic_cast <QWidget *> (parent());
    QX11Info xInfo = x11Info();

    widgetHandle = Ogre::StringConverter::toString ((unsigned long)xInfo.display()) +
        ":" + Ogre::StringConverter::toString ((unsigned int)xInfo.screen()) +
        ":" + Ogre::StringConverter::toString ((unsigned long)q_parent->winId());

#endif
    viewConfig["externalWindowHandle"] = widgetHandle;
    mWindow = mRoot->createRenderWindow("Ogre rendering window",
                width(), height(), false, &viewConfig);

    camera = mSceneMgr->createCamera("myCamera");
    Ogre::Vector3 camPos(0, 50,150);
        camera->setPosition(camPos);
        camera->lookAt(0,50,0);
    emit cameraPositionChanged(camPos);

    ogreViewport = mWindow->addViewport(camera);
    ogreViewport->setBackgroundColour(Ogre::ColourValue(0,0,255));
    camera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));

        setupNLoadResources();
        createScene();
}
*/
/*****************************************************************************/

void AppWidget::setupNLoadResources()
{
        // Load resource paths from config file
        Ogre::ConfigFile cf;
        cf.load("resources.cfg");

        // Go through all sections & settings in the file
        Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

        Ogre::String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
                secName = seci.peekNextKey();
                Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
                Ogre::ConfigFile::SettingsMultiMap::iterator i;
                for (i = settings->begin(); i != settings->end(); ++i)
                {
                        typeName = i->first;
                        archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
                        // OS X does not set the working directory relative to the app,
                        // In order to make things portable on OS X we need to provide
                        // the loading with it's own bundle path location
                        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                                Ogre::String(macBundlePath() + "/" + archName), typeName, secName);
#else
                        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                                archName, typeName, secName);
#endif
                }
        }

        // Initialise, parse scripts etc
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

/*****************************************************************************/

void AppWidget::createScene()
{
        mSceneMgr->setAmbientLight(Ogre::ColourValue(1,1,1));

        /*Ogre::Entity *robotEntity = mSceneMgr->createEntity("Robot" ,"models/robot.mesh");
        Ogre::SceneNode *robotNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RobotNode");
        robotNode->attachObject(robotEntity);
        robotNode->yaw(Ogre::Radian(Ogre::Degree(-90)));*/
}

