#ifndef PIECE_H
#define PIECE_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Base.h"
#include "Volume.h"

class Fuselage;
class InputListener;

/////////////////////////////////////////////////
/// \brief
///
///
/////////////////////////////////////////////////
class Piece : public Base
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Piece(Fuselage& _fuselage,float mass,ArrayPoints &polygone,Ogre::Vector3 offset,Relative _stickFace,Ogre::Vector3 position);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Piece();


    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param face Indique la face qui va retourner sa position
    /// \return Position de la face sur l'axe indiquer par la face
    ///
    /////////////////////////////////////////////////
    float getPositionFace(Relative face);

    /////////////////////////////////////////////////
    /// \brief
    ///
    /// \param face Indique la face qui va retourner sa position
    /// \return Position de la face sur l'axe indiquer par la face
    ///
    /////////////////////////////////////////////////
    Relative getStickFace()
    {
        return stickFace;
    }

    /////////////////////////////////////////////////
    /// \brief Move position of piece
    ///
    /// \param axe1
    /// \param axe2
    ///
    /////////////////////////////////////////////////
    void Move(float axe1,float axe2);

    /////////////////////////////////////////////////
    /// \brief Change face what magnetism piece
    ///
    /// \param face what will magnetism piece
    ///
    /////////////////////////////////////////////////
    void PositionTo(Relative face);

    /////////////////////////////////////////////////
    /// \brief set new position and magnetisme to fuselage
    ///
    /// \param position new position before aply magnetisme
    ///
    /////////////////////////////////////////////////
    void setPosition(Ogre::Vector3 position);

    /////////////////////////////////////////////////
    /// \brief Stick piece on fuselage's face select by PositionTo
    ///
    /////////////////////////////////////////////////
    void MagnetismFuselage();

    /////////////////////////////////////////////////
    /// \brief Stick piece on fuselage's face select by parameter
    ///
    /// \param face select face who will magnetism the piece
    ///
    /////////////////////////////////////////////////
    void MagnetismFuselage(Relative face);

    /////////////////////////////////////////////////
    /// \brief Check and correct if piece is out of fuselage
    ///
    /////////////////////////////////////////////////
    void DontLeaveFuselage();

    void CorrectCollission();

    /////////////////////////////////////////////////
    /// \brief Calcule le centre de gravité de la piece
    /// Le calcul utilise les points comme reference
    ///
    /////////////////////////////////////////////////
    void CalculateGravityCenter();

    /////////////////////////////////////////////////
    /// \brief Display some information on piece in console
    ///
    /////////////////////////////////////////////////
    void Display();

    Fuselage& getParentSection(){return fuselage;};

public:
    ///Where is this piece in XML file
    std::string file;
    std::string name;

private:
    Fuselage &          fuselage;           ///< Ref to parent fuselage manualBox
    Volume              volume;             ///< Volume of piece
    Relative            stickFace;          ///< Select face what magnetism the piece
    ArrayPoints         points;             ///< Shape of piece

    friend InputListener;
};

#endif // PIECE_H
