#ifndef SCENE_H
#define SCENE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre.h>
#include <memory>
#include <list>
#include <vector>
#include "Volume.h"
#include "DisplayObject.h"

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

    void DisplayGravityCenterAllEntity();

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
    DisplayObject gravityCenter;
    /** Zone aim to gravity center */
    DisplayObject gravityBalance;
};

#endif // SCENE_H
