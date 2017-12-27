/*
Student: James Brooks
Class: Game Architecture

File: TextureAsset.cpp

Class: TextureAsset

Description: An asset that holds an image to be used as a texture.
*/


#include "Core.h"

#include "TextureAsset.h"


TextureAsset::TextureAsset(unsigned int uniqueID) : Asset(uniqueID) {

    fileName = "";
}


TextureAsset::~TextureAsset() {


}

void TextureAsset::load(std::unique_ptr<FileSystem::FileAccessor> element) {

    //FileSystem::Instance(). FirstChildElement("filename");

    /*if (fileElement != NULL) {

        fileName = fileElement->GetText();
    }
    else {

        std::cerr << "Could not find file to load for texture asset." << std::endl;
    }*/
}
