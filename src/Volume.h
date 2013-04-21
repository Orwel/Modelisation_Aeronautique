#ifndef VOLUME_H
#define VOLUME_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Ogre.h>

typedef std::vector<Ogre::Vector3> ArrayPoints;

/////////////////////////////////////////////////
/// \brief Define six face on rectangular parallelepiped
///
/////////////////////////////////////////////////
enum Relative
{
    NONE,
    POS_X,
    POS_Y,
    POS_Z,
    NEG_X,
    NEG_Y,
    NEG_Z
};

/////////////////////////////////////////////////
/// \brief Define rectangular parallelepiped
///
/////////////////////////////////////////////////
class Volume
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Volume();

    /////////////////////////////////////////////////
    /// \brief Constructorc from values
    ///
    /// \param weight
    /// \param heigth
    /// \param depth
    ///
    /////////////////////////////////////////////////
    Volume(float weight,float heigth,float depth);

    /////////////////////////////////////////////////
    /// \brief Constructorc to create box from array points
    ///
    /// \param points define shape for volume box this shape
    ///
    /////////////////////////////////////////////////
    Volume(ArrayPoints& points);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Volume();

    /////////////////////////////////////////////////
    /// \brief Return position of the face
    ///
    /// \param face
    /// \return position of face
    ///
    /////////////////////////////////////////////////
    float getPositionFace(Relative face);

    /////////////////////////////////////////////////
    /// \brief Return position of the face with offset
    ///
    /// \param pos  offset from position of rectangular parallelepiped
    /// \param face
    /// \return position of face
    ///
    /////////////////////////////////////////////////
    float getPositionFace(Ogre::Vector3 pos,Relative face);

    /////////////////////////////////////////////////
    /// \brief Add some points in array to define rectangular parallelepiped
    ///
    /// \param points array of point
    ///
    /////////////////////////////////////////////////
    void addArrayPoint(ArrayPoints& points);

    static void MinMaxFromPoints(ArrayPoints& points,Ogre::Vector3& min,Ogre::Vector3& max);

    static bool getRelatif(std::string str,Relative &relative);

public:
    float w;        ///< Weight
    float h;        ///< Heigth
    float d;        ///< Depth

};

#endif // VOLUME_H
