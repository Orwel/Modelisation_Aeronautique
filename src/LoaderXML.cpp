#include "LoaderXML.h"
#include "TinyXML/FunctionXML.h"
#include "Scene.h"
#include "Fuselage.h"
#include "Piece.h"

using namespace tinyxml2;

void LoadSection(XMLElement *element,Scene &scene);
void LoadPiece(XMLElement *element,Fuselage &Fuselage);


LoaderXML::LoaderXML():directory("rsc/")
{

}

LoaderXML::~LoaderXML()
{

}

void LoaderXML::LoadModel(Scene &scene,const std::string &patch)
{
    std::string directory("../../rsc/");
    std::string patch_file = directory+patch;
    XMLDocument doc;
    int result = doc.LoadFile(patch_file.c_str());
    if(result!=XML_NO_ERROR)
    {
        doc.PrintError();
        FatalError("LoaderXML::LoadModel => To load "+patch_file);
    }
    XMLElement *element = doc.FirstChildElement("ModelisationFactory");
    if(element==nullptr)
        FatalError("LoaderXML::LoadModel => Root is not ModelisationFactory in "+patch_file);
    element = element->FirstChildElement();
    if(element == nullptr)
    {
        FatalError("LoaderXML::LoadModel => No child in "+patch_file);
    }
    else if(std::string(element->Name())=="Model")
    {
        std::string name = getStringAttribute(element,"name");
        for(   ; element != nullptr ; element = element->NextSiblingElement())
        {
            if(std::string(element->Name())=="Section")
                LoadSection(element,scene);
            else
                FatalError("LoaderXML::LoadModel => Child of Model is not section in "+patch_file);
        }
    }
    else
    {
        FatalError("LoaderXML::LoadModel => First child is not Model in "+patch_file);
    }
}


void LoadSection(XMLElement *sectionXML,Scene &scene)
{
    float mass,thickness;
    Volume total;
    Ogre::Vector3 position;
    mass = getFloatAttribute(sectionXML,"mass");
    position.x = getFloatAttribute(sectionXML,"x");
    position.y = getFloatAttribute(sectionXML,"y");
    position.z = getFloatAttribute(sectionXML,"z");
    total.w = getFloatAttribute(sectionXML,"w");
    total.h = getFloatAttribute(sectionXML,"h");
    total.d = getFloatAttribute(sectionXML,"d");
    thickness = getFloatAttribute(sectionXML,"thickness");
    Fuselage* fuselage = new Fuselage(scene,mass,total,thickness);

    sectionXML = sectionXML->FirstChildElement();
    for(   ; sectionXML != nullptr ; sectionXML = sectionXML->NextSiblingElement())
    {
        if(std::string(sectionXML->Name())=="PlacePiece")
            LoadPiece(sectionXML,*fuselage);
    }

}

void LoadPiece(XMLElement *placePiece,Fuselage &fuselage)
{
    XMLElement* pieceXML = placePiece->FirstChildElement();
    if(pieceXML==nullptr)
        FatalError("LoaderXML::LoadPiece => PlacePiece dont have child");
    XMLElement* polygonXML = pieceXML->FirstChildElement();
    if(pieceXML==nullptr)
        FatalError("LoaderXML::LoadPiece => Piece dont have child ");

    float mass;
    Ogre::Vector3 position,offset;
    ArrayPoints polygon;
    Relative stickFace;
    position.x = getFloatAttribute(placePiece,"x");
    position.y = getFloatAttribute(placePiece,"y");
    position.z = getFloatAttribute(placePiece,"z");
    if(getStringAttribute(placePiece,"stickFace")=="pos_x")
        stickFace = POS_X;
    else if(getStringAttribute(placePiece,"stickFace")=="neg_x")
        stickFace = NEG_X;
    else if(getStringAttribute(placePiece,"stickFace")=="pos_y")
        stickFace = POS_Y;
    else if(getStringAttribute(placePiece,"stickFace")=="neg_y")
        stickFace = NEG_Y;
    else if(getStringAttribute(placePiece,"stickFace")=="pos_z")
        stickFace = POS_Z;
    else if(getStringAttribute(placePiece,"stickFace")=="neg_z")
        stickFace = NEG_Z;

    mass = getFloatAttribute(pieceXML,"mass");
    for(XMLElement* vertexXML = polygonXML->FirstChildElement();vertexXML!=nullptr;vertexXML = vertexXML->NextSiblingElement())
    {
        if(std::string(vertexXML->Name())=="Vertex")
        {
            Ogre::Vector3 point;
            point.x = getFloatAttribute(vertexXML,"x");
            point.y = getFloatAttribute(vertexXML,"y");
            polygon.push_back(point);
        }
        else if(std::string(vertexXML->Name())=="Offset")
        {
            offset.x = getFloatAttribute(vertexXML,"x");
            offset.y = getFloatAttribute(vertexXML,"y");
            offset.z = getFloatAttribute(vertexXML,"z");
        }
        else
        {
            FatalError("LoaderXML::LoadPiece => Unknow child "+std::string(vertexXML->Name())+" in Piece");
        }
    }
    Piece *piece = new Piece(fuselage,mass,polygon,offset,stickFace);
}
