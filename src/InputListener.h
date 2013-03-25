#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <Ogre.h>
#include <OIS.h>
#include "Scene.h"
#include "OrbitCamera.h"

using namespace Ogre;
using namespace OIS;

/**
*   Gestion des evenement provenant de la fenetre, du clavier, de la souris
*/
class InputListener: public FrameListener, public WindowEventListener, public KeyListener, public MouseListener
{
public:
    /** Constructor */
    InputListener(Scene *_scene,SceneManager* _sceneManager,RenderWindow* _window,OrbitCamera* _orbitCamera);
    /** Destructor */
    virtual ~InputListener();

private:
    /** Initialise la gestion des inputs */
	void startOIS ();
    // ci-dessous, l'implementation des methodes purement virtuelles permettant de gerer les inputs
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
    /** La scene contenant les objets a manipuler */
	Scene *scene;
	/** Le scene manager, qui cree les objets */
	SceneManager* sceneManager;
	/** La fenetre de l'application */
	RenderWindow* windows;
	/** La camera à gerer avec les touches de clavier et la souris */
	OrbitCamera* orbitCamera;

	/** permet de gerer les inputs */
	InputManager* inputManager;
	/** Permet de capter les inputs de la souris */
	Mouse* mMouse;
	/** Permet de capter les inputs du clavier */
	Keyboard* mKeyboard;

    /** Tant que vrai, le programe s'execute */
    bool mContinuer;
};

#endif // INPUTLISTENER_H
