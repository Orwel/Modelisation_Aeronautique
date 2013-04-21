#include "LoaderXML.h"
#include "TinyXML/FunctionXML.h"
#include "Scene.h"
#include "Fuselage.h"
#include "Piece.h"

using namespace tinyxml2;

XMLElement* LoadDocument(XMLDocument& doc,std::string file);
void LoadSection(XMLElement *element,Scene &scene);
void LoadPlacePiece(XMLElement *placePiece,Fuselage &fuselage);
Piece* LoadPiece(XMLElement *element,Fuselage &Fuselage,Relative stickFace);


LoaderXML::LoaderXML():directory("rsc/")
{

}

LoaderXML::~LoaderXML()
{

}

/*****************************************************************************/
XMLElement* LoadDocument(XMLDocument& doc,std::string patch)
{
    std::string directory("../../rsc/");
    std::string patch_file = directory+patch;
    ;
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
    return element;
}

/*****************************************************************************/
void LoaderXML::LoadModel(Scene &scene,const std::string &patch)
{
    XMLDocument doc;
    XMLElement* modelXML = LoadDocument(doc,patch);

    if(modelXML == nullptr)
    {
        FatalError("LoaderXML::LoadModel => No child in "+patch);
    }
    else if(std::string(modelXML->Name())=="Model")
    {
        std::string nameModel = getStringAttribute(modelXML,"name");
        for(XMLElement* sectionXML = modelXML->FirstChildElement() ; sectionXML != nullptr ; sectionXML = sectionXML->NextSiblingElement())
        {
            if(std::string(sectionXML->Name())=="Section")
                LoadSection(sectionXML,scene);
            else
                FatalError("LoaderXML::LoadModel => Child of Model is not section in "+patch);
        }
    }
    else
    {
        FatalError("LoaderXML::LoadModel => First child is not Model in "+patch);
    }
}

/*****************************************************************************/
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
    fuselage->setPosition(position);

    sectionXML = sectionXML->FirstChildElement();
    for(   ; sectionXML != nullptr ; sectionXML = sectionXML->NextSiblingElement())
    {
        if(std::string(sectionXML->Name())=="PlacePiece")
            LoadPlacePiece(sectionXML,*fuselage);
    }
}

/*****************************************************************************/
void LoadPlacePiece(XMLElement *placePiece,Fuselage &fuselage)
{
    XMLElement* pieceXML = placePiece->FirstChildElement();
    if(pieceXML==nullptr)
        FatalError("LoaderXML::LoadPlacePiece => PlacePiece dont have child");

    Ogre::Vector3 position;
    Relative stickFace;
    position.x = getFloatAttribute(placePiece,"x");
    position.y = getFloatAttribute(placePiece,"y");
    position.z = getFloatAttribute(placePiece,"z");


    std::string str_stickFace = getStringAttribute(placePiece,"stickFace");
    if(!Volume::getRelatif(str_stickFace,stickFace))
        FatalError("LoaderXML::LoadPlacePiece => attribut stickFace have fail value :"+str_stickFace);

    Piece* piece = nullptr;
    if(std::string(pieceXML->Name())=="Piece")
        piece = LoadPiece(pieceXML,fuselage,stickFace);
    else if(std::string(pieceXML->Name())=="LoadPiece")
    {
        std::string file = getStringAttribute(pieceXML,"file");
        std::string name = getStringAttribute(pieceXML,"name");

        XMLDocument doc;
        pieceXML = LoadDocument(doc,file);
        while(pieceXML!=nullptr)
        {
            if(std::string(pieceXML->Name())=="Piece" && getStringAttribute(pieceXML,"name")==name)
            {
                piece = LoadPiece(pieceXML,fuselage,stickFace);
                break;
            }
            pieceXML = pieceXML->NextSiblingElement();
        }
        //If piece is not found
        if(piece == nullptr)
        {
            FatalError("LoaderXML::LoadPlacePiece => LoadPiece fail from file and name"+file+"  "+name);
        }

    }
    else
        FatalError("LoaderXML::LoadPlacePiece => PlacePiece have unknow child "+std::string(pieceXML->Name()));
    piece->setPosition(position);
}

/*****************************************************************************/
Piece* LoadPiece(XMLElement *pieceXML,Fuselage &fuselage,Relative stickFace)
{
    XMLElement* polygonXML = pieceXML->FirstChildElement("Polygon");
    if(polygonXML==nullptr)
        FatalError("LoaderXML::LoadPiece => Piece dont have child Polygon");
    XMLElement* offsetXML = pieceXML->FirstChildElement("Offset");
    if(offsetXML==nullptr)
        FatalError("LoaderXML::LoadPiece => Piece dont have child Offset");

    float mass;
    Ogre::Vector3 offset;
    ArrayPoints polygon;

    offset.x = getFloatAttribute(offsetXML,"x");
    offset.y = getFloatAttribute(offsetXML,"y");
    offset.z = getFloatAttribute(offsetXML,"z");

    mass = getFloatAttribute(pieceXML,"mass");

    for(XMLElement* vertexXML = polygonXML->FirstChildElement(); vertexXML!=nullptr; vertexXML = vertexXML->NextSiblingElement())
    {
        if(std::string(vertexXML->Name())=="Vertex")
        {
            Ogre::Vector3 point;
            point.x = getFloatAttribute(vertexXML,"x");
            point.y = getFloatAttribute(vertexXML,"y");
            point.z = 0;
            polygon.push_back(point);
        }
        else
        {
            FatalError("LoaderXML::LoadPiece => Piece have unknow child "+std::string(vertexXML->Name()));
        }
    }
    return new Piece(fuselage,mass,polygon,offset,stickFace);
}

