#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <Ogre.h>
#include <OIS.h>
#include "Scene.h"
#include "OrbitCamera.h"

using namespace Ogre;
using namespace OIS;

class InputListener: public FrameListener, public WindowEventListener, public KeyListener, public MouseListener
{
public:
    InputListener(Scene *_scene,SceneManager* _sceneManager,RenderWindow* _window,OrbitCamera* _orbitCamera);
    virtual ~InputListener();

private:
    /** Initialise la gestion des inputs */
	void startOIS ();
    // ci-dessous, l'implémentation des méthodes purement virtuelles permettant de gérer les inputs
	// FrameListener
	bool frameRenderingQueued (const FrameEvent& evt);

	// WindowEventListener
	virtual void windowResized (RenderWindow* rw);
	virtual void windowClosed (RenderWindow* rw);

	// MouseListener
	virtual bool mouseMoved (const MouseEvent &e);
	virtual bool mousePressed (const MouseEvent &arg, MouseButtonID id);
	virtual bool mouseReleased (const MouseEvent &arg, MouseButtonID id);

	// KeyListener
	virtual bool keyPressed (const KeyEvent &e);
	virtual bool keyReleased (const KeyEvent &e);

private:
    /** La scène contenant les objets à manipuler */
	Scene *scene;
	/** Le scene manager, qui crée les objets */
	SceneManager* sceneManager;
	/** La fenêtre de l'application, créée dans ShortStory */
	RenderWindow* windows;
	/** La caméra à gérer avec les touches de clavier et la souris (créée dans ShortStory) */
	OrbitCamera* orbitCamera;

	/** permet de gérer les inputs */
	InputManager* inputManager;
	/** Permet de capter les inputs de la souris */
	Mouse* mMouse;
	/** Permet de gérer les inputs du clavier */
	Keyboard* mKeyboard;

    /** Tant que vrai, le programe s'exécute */
    bool mContinuer;
};

#endif // INPUTLISTENER_H
