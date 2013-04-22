#ifndef COLOURCONSTANT_H_INCLUDED
#define COLOURCONSTANT_H_INCLUDED

#include <Ogre.h>

namespace ColourConstant
{
const Ogre::ColourValue balanceGravity(Ogre::ColourValue(1,0,1));
const Ogre::ColourValue gravityCenterModel(Ogre::ColourValue(1,0,0.7));

const Ogre::ColourValue piece(Ogre::ColourValue::Blue);
const Ogre::ColourValue pieceBox(Ogre::ColourValue::White);
const Ogre::ColourValue gravityCenterPiece(Ogre::ColourValue::Green);

const Ogre::ColourValue fuselage(Ogre::ColourValue::White);
const Ogre::ColourValue fuselageBox(Ogre::ColourValue::Red);
const Ogre::ColourValue gravityCenterFuselage(Ogre::ColourValue::Green);
}
#endif // COLOURCONSTANT_H_INCLUDED
