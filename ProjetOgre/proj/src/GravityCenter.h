#ifndef GRAVITYCENTER_H
#define GRAVITYCENTER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre.h>
#include "Volume.h"

class Scene;

/////////////////////////////////////////////////
/// \brief Center of gravity
/// Create display object to display gravity center
///
/////////////////////////////////////////////////
class GravityCenter
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    GravityCenter(Scene& _scene, Ogre::SceneNode * parent=nullptr);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~GravityCenter();

    /////////////////////////////////////////////////
    /// \brief Envoie l'origine pour dessiner le centre de gravite
    ///
    /// \param parent Noeud qui sert de rep�re pour dessiner le centre de gravite
    ///
    /////////////////////////////////////////////////
    void setParentSceneNode(Ogre::SceneNode * parent);

    /////////////////////////////////////////////////
    /// \brief Retourne la position du centre de gravite
    ///
    /// \return position du centre de gravite
    ///
    /////////////////////////////////////////////////
    Ogre::Vector3 getPosition();

    /////////////////////////////////////////////////
    /// \brief Envoie une nouvelle position pour le centre de gravite
    ///
    /// \param position nouvelle position pour le centre de gravite
    ///
    /////////////////////////////////////////////////
    void setPosition(Ogre::Vector3 position);

    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param
    /// \return
    ///
    /////////////////////////////////////////////////
    static Ogre::Vector3 averagePoints(ArrayPoints points);

private:

    /////////////////////////////////////////////////
    /// \brief Cr�er les objets � afficher pour representer le centre de gravite
    ///
    /////////////////////////////////////////////////
    void CreateGravityObject();

private:
    Scene&              scene;              ///< Ref to scene
    Ogre::SceneNode *   node;               ///< Main node for display object
    Ogre::ManualObject* manualObject;       ///< Display object
};

#endif // GRAVITYCENTER_H
