#include <QtGui/QApplication>
#include <QtCore/QDir>

#include "mainwindow.h"

#include <OgrePrerequisites.h>
#include <Ogre.h>

#include <string>

std::string bundlePath()
{
    return "" ;
}

std::string resourcePath()
{
    return bundlePath();
}

Ogre::Root *mOgreRoot;

void setupOgre(Ogre::String plugins, Ogre::String config, Ogre::String log)
{
    // create the main ogre object
    mOgreRoot = new Ogre::Root( plugins);

#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
    // load additional plugins
    const Ogre::String& pluginPathDepends = "../../Dependencies/lib/";
    mOgreRoot->loadPlugin(pluginPathDepends + "libCaelum.so");
#endif

    Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_BOREME);

    Ogre::ConfigFile cf;
    std::string cfPath = resourcePath();
    cfPath.append("resources.cfg");
    cf.load(cfPath);

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
            archName = resourcePath() + i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }

#if ((OGRE_VERSION_MAJOR * 10) + OGRE_VERSION_MINOR) >= 17
    Ogre::RenderSystemList::const_iterator pRend = mOgreRoot->getAvailableRenderers().begin();
    while (pRend != mOgreRoot->getAvailableRenderers().end())
#else
        Ogre::RenderSystemList::const_iterator pRend = mOgreRoot->getAvailableRenderers()->begin();
    while (pRend != mOgreRoot->getAvailableRenderers()->end())
#endif
    {
        Ogre::String rName = (*pRend)->getName();
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        if (rName == "Direct3D9 Rendering Subsystem")
#else
        if (rName == "OpenGL Rendering Subsystem")
#endif
            break;
        pRend++;
    }

    Ogre::RenderSystem *rsys = *pRend;

    // Some standard rendering system configurations
    rsys->setConfigOption("VSync", "No"); // -> Why not?

    // Set the rendering system and Initialise OGRE
    mOgreRoot->setRenderSystem(rsys);

    // initialize without creating window
    mOgreRoot->getRenderSystem()->setConfigOption( "Full Screen", "No" );
    //mOgreRoot->saveConfig();
    mOgreRoot->initialise(false); // don't create a window

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(a.applicationDirPath());

    a.setOrganizationName("Polytech");
    a.setApplicationName("modele");

    //setupOgre(resourcePath() + Ogre::String("plugins.cfg"), Ogre::String("ogre.cfg"), Ogre::String("ogitor.log"));

    MainWindow w;
    w.show();
    int retval = a.exec();

    //delete mOgreRoot;

    return retval;
}
