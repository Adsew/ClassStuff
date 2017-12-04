/*
Student: James Brooks
Class: Game Architecture

File: TextureAsset.h

Class: TextureAsset

Description: An asset that holds an image to be used as a texture.
*/


#include "TextureAsset.h"


using namespace tinyxml2;


TextureAsset::TextureAsset() {

    fileName = "";
}


TextureAsset::~TextureAsset() {


}

void TextureAsset::load(XMLElement *element) {

    XMLElement *fileElement = element->FirstChildElement("filename");

    if (fileElement != NULL) {

        fileName = fileElement->GetText();
    }
    else {

        std::cerr << "Could not find file to load for texture asset." << std::endl;
    }
}
