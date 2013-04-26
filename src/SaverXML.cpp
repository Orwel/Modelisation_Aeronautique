#include "SaverXML.h"
#include "TinyXML/FunctionXML.h"
#include "Scene.h"
#include "Fuselage.h"
#include "Piece.h"

using namespace tinyxml2;

void PrintSection(XMLDocument &doc,XMLElement *modelXML,Fuselage& section);
void PrintPlacePiece(XMLDocument &doc,XMLElement *sectionXML,Piece& piece);

/*****************************************************************************/
void SaveModel(Scene &scene,const std::string &patch)
{
    std::string directory("../../rsc/");
    std::string patch_file = directory+patch;

    XMLDocument doc;
	XMLElement* root,*modelXML;
	// <?xml version="1.0" standalone="yes"?>
 	XMLDeclaration* decl = doc.NewDeclaration();
 	doc.LinkEndChild(decl);

    root = doc.NewElement("ModelisationFactory");
    doc.LinkEndChild(root);

    modelXML = doc.NewElement("Model");
    root->LinkEndChild(modelXML);
    modelXML->SetAttribute("name",scene.name.c_str());

    for(auto& section:scene.sections)
    {
        PrintSection(doc,modelXML,*section.get());
    }

	doc.SaveFile(patch_file.c_str());
}

/*****************************************************************************/
void PrintSection(XMLDocument &doc,XMLElement *modelXML,Fuselage& section)
{
    XMLElement* sectionXML = doc.NewElement("Section");
    modelXML->LinkEndChild(sectionXML);

    sectionXML->SetAttribute("mass",section.mass);
    sectionXML->SetAttribute("x",section.getPosition().x);
    sectionXML->SetAttribute("y",section.getPosition().y);
    sectionXML->SetAttribute("z",section.getPosition().z);
    sectionXML->SetAttribute("w",section.total.w);
    sectionXML->SetAttribute("h",section.total.h);
    sectionXML->SetAttribute("d",section.total.d);
    sectionXML->SetAttribute("thickness",section.total.w-section.volume.w);

    for(auto& piece:section.pieces)
    {
        PrintPlacePiece(doc,sectionXML,*piece.get());
    }
}

/*****************************************************************************/
void PrintPlacePiece(XMLDocument &doc,XMLElement *sectionXML,Piece& piece)
{
    XMLElement* placePieceXML = doc.NewElement("PlacePiece");
    XMLElement* loadPieceXML  = doc.NewElement("LoadPiece");
    sectionXML->LinkEndChild(placePieceXML);
    placePieceXML->LinkEndChild(loadPieceXML);

    placePieceXML->SetAttribute("x",piece.getPosition().x);
    placePieceXML->SetAttribute("y",piece.getPosition().y);
    placePieceXML->SetAttribute("z",piece.getPosition().z);
    placePieceXML->SetAttribute("stickFace",Volume::getStringFromRelatif(piece.getStickFace()).c_str());

    loadPieceXML->SetAttribute("file",piece.file.c_str());
    loadPieceXML->SetAttribute("name",piece.name.c_str());
}
