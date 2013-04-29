#ifndef APPLICATION_H
#define APPLICATION_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre.h>
#include "OrbitCamera.h"
#include "InputListener.h"
#include "Scene.h"

using namespace Ogre;


////////////////////////////////////////////////////////////
/// \brief Classe permettant d'initialiser un projet, et contenant la boucle de rendu.
/// Il faut commencer par appeler la m�thode Initialize() puis start() qui lancera la boucle de rendu.
////////////////////////////////////////////////////////////
class Application
{
public:
    /** Constructor */
    Application();

    /** Destructor */
    ~Application();

    /** Initialise l'appli Ogre, notamment la gestion des inputs */
    bool Initialize ();

    /** Lance la boucle de rendu */
    bool start ();

private:
    /** Initialise la scene */
    void initScene ();

private:
    /** La racine de Ogre */
    Root *mRoot;
    /** Le renderWindow, la fen�tre de l'appli */
    RenderWindow* mWindow;
    /** Le scene manager, qui cr�e les objets */
    SceneManager* mSceneMgr;
    /** L'objet qui cr�ait et manipule la sc�ne */
    Scene* scene;
    /** Le comportement de la cam�ra */
    OrbitCamera* orbitalCamera;
    /** La cam�ra */
    Camera* camera;
    /** Le noeud de la cam�ra */
    SceneNode* nCamera;
    /** Le gestionnaire d'input */
    InputListener* inputListener;
};

#endif // APPLICATION_H
