#ifndef SCENE_H
#define SCENE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre.h>
#include <Memory>
#include <List>
#include "Volume.h"
#include "GravityCenter.h"

class Fuselage;
class Piece;
typedef std::unique_ptr<Fuselage> FuselagePtr;
typedef std::vector<FuselagePtr> ListFuselagePtr;

/**
*   Cet objet manipule l'ensemble des objets contenu dans la scene
*/
class Scene
{
public:
    /** Constructor */
    Scene(Ogre::SceneManager *_sceneManager);
    /** Destructor */
    ~Scene();

    void AddFuselage(Fuselage *fuselage);
    void DeleteFuselage(Fuselage *fuselage);
    void ClearFuselages();

    /** Move selected piece */
    void moveSelectedPiece(float x,float y,float z);
    /** Return true if piece is selected */
    bool isPieceSelected();
    /** Change le magnetism de la piece selectionne */
    void setMagnetism(Relative face);

    /** Calcule et place le centre de gravite du modele */
    void CalculateGravityCenter();

    /** Create with ManualObject */
    Ogre::ManualObject * createPavet(Volume volume, Ogre::ColourValue colour, const char * name=nullptr);
    Ogre::ManualObject * createPolygon3D(ArrayPoints &polygone,Ogre::ColourValue colour, const char * name=nullptr);

private:
    /** Lumieres */
    void setLight();

public:
    /** Le scene manager */
    Ogre::SceneManager * sceneManager;
    /** Noeud indiquant le centre du monde */
    Ogre::SceneNode* nCenter;
    /** Noeud parent des elements du modele */
    Ogre::SceneNode* nPattern;
    /** Listes des sections du fuselage */
    ListFuselagePtr sections;
    /** Piece selectionnee */
    Piece * selected;
    /** Centre de gravite du modele */
    GravityCenter gravityCenter;
};

#endif // SCENE_H
