#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>

class AppWidget : public QWidget
{
    Q_OBJECT
public:
    /** Constructor */
    AppWidget(QWidget *parent = 0);

    /** Destructor */
    ~AppWidget();
    
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

#endif // APPWIDGET_H
