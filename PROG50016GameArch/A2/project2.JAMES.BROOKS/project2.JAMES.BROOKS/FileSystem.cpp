/*
Student: James Brooks
Class: Game Architecture

File: FileSyster.cpp

Class: FileSystem

Description: Lowest level of file loading. Calling this can return a file element
    to be sifted through for data.
*/


#include "Core.h"

#include "AssetManager.h"
#include "FileSystem.h"


void FileSystem::initialize() {


}

void FileSystem::update(float _deltaTime) {


}

void FileSystem::load(std::string name) {

    XMLDocument doc;

    doc.LoadFile(name.c_str());

    if (doc.ErrorID() == XML_NO_ERROR) {

        XMLElement *elem = NULL;
        
        elem = doc.FirstChildElement("Assets");

        if (elem != NULL) {

            AssetManager::Instance().load(elem);
        }
    }
    else {

        std::cerr << "Error loading file " << name << std::endl;
    }
}
