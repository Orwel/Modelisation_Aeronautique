#include "tinyxml2.h"
#include <iostream>
////////////////////////////////////////////////////////////
void FatalError(std::string msg)
{
    std::cerr<<"Error: "<<msg<<std::endl;
    exit(EXIT_FAILURE);
}

/** \brief Return value attribute of type int. If Query fail, exit program
 *
 * \param element   Element what contain attribute is query
 * \param name      attribute'name
 * \return int value of attribute
 *
 */
inline int getIntAttribute(const tinyxml2::XMLElement *element,const std::string &name)
{
    int value;
    int result = element->QueryIntAttribute(name.c_str(),&value);
    if(result != tinyxml2::XML_NO_ERROR)
    {
        FatalError("XMLFunction getIntAttribute => attribute is "+name);
    }
    return value;
}

/** \brief Return value attribute of type float. If Query fail, exit program
 *
 * \param element   Element what contain attribute is query
 * \param name      attribute'name
 * \return float value of attribute
 *
 */
inline float getFloatAttribute(const tinyxml2::XMLElement *element,const std::string &name)
{
    float value;
    int result = element->QueryFloatAttribute(name.c_str(),&value);
    if(result != tinyxml2::XML_NO_ERROR)
    {
        FatalError("XMLFunction getIntAttribute => attribute is "+name);
    }
    return value;
}

/** \brief Return value attribute of type string. If Query fail, exit program
 *
 * \param element   Element what contain attribute is query
 * \param name      attribute'name
 * \return string value of attribute
 *
 */
inline std::string getStringAttribute(const tinyxml2::XMLElement *element,const std::string &name)
{
    const char * str = element->Attribute(name.c_str());
    if(str == nullptr)
    {
        FatalError("XMLFunction getStringAttribute => attribute is "+name);
    }
    return std::string(str);
}
