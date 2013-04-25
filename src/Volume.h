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

    ////////////////////////////////////////////////////////////
    /// \brief All attributs divide by 2
    ///
    ////////////////////////////////////////////////////////////
    void half();

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


    /////////////////////////////////////////////////
    /// \brief Find min and max for each axis
    /// min.x and min.y can not provide same point
    ///
    /// \param  points array points
    /// \param  min ref to min value who will be return
    /// \param  max ref to max value who will be return
    ///
    /////////////////////////////////////////////////
    static void MinMaxFromPoints(ArrayPoints& points,Ogre::Vector3& min,Ogre::Vector3& max);

    /////////////////////////////////////////////////
    /// \brief return average point
    ///
    /// \param  points array points to make average
    /// \return average point
    ///
    /////////////////////////////////////////////////
    static Ogre::Vector3 averagePoints(ArrayPoints points);


    /////////////////////////////////////////////////
    /// \brief get relatif from string name
    ///
    /// \param str  string name of relatif
    /// \param relative orresponding string name
    /// \return true if name exist, else false
    ///
    /////////////////////////////////////////////////
    static bool getRelatif(std::string str,Relative &relative);

    /////////////////////////////////////////////////
    /// \brief get relatif from string name
    ///
    /// \param str  string name of relatif
    /// \param relative orresponding string name
    /// \return true if name exist, else false
    ///
    /////////////////////////////////////////////////
    static std::string getStringFromRelatif(Relative relative);

    static bool boxCollide(Volume box1,Ogre::Vector3 pos1,Volume box2,Ogre::Vector3 pos2);
    static bool boxCollide(Volume box1,Ogre::Vector3 pos1,Volume box2,Ogre::Vector3 pos2,Ogre::Vector3 &intersection);

public:
    float w;        ///< Weight
    float h;        ///< Heigth
    float d;        ///< Depth

};

#endif // VOLUME_H
