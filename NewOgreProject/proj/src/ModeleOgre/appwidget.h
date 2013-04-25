#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>
#include <QtGui>
#include <Ogre.h>
#include <QtGui/QX11Info>
#include "OrbitCamera.h"
#include "InputListener.h"
#include "Scene.h"

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

    QPaintEngine* paintEngine() const; // Turn off QTs paint engine for the Ogre widget.


private:
    /** Initialise la scene */
    void initScene ();
    void initMyScene();

public slots:
    void setBackgroundColor(QColor c);
    void setCameraPosition(const Ogre::Vector3 &pos);

signals:
    void cameraPositionChanged(const Ogre::Vector3 &pos);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void moveEvent(QMoveEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void showEvent(QShowEvent *e);
    virtual void wheelEvent(QWheelEvent *e);

private:
    void initOgreSystem();
    void setupNLoadResources();
    void createScene();

private:
    static const Ogre::Real turboModifier;
    static const QPoint invalidMousePoint;

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

    Ogre::Viewport *ogreViewport;

    QPoint oldPos;
    
};

#endif // APPWIDGET_H
