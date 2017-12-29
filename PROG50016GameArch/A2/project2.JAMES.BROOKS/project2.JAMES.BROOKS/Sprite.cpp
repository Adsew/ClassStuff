/*
Student: James Brooks
Class: Game Architecture

File: Sprite.cpp

Class: Sprite

Description: A small image to be rendered to the screen.
*/


#include "Core.h"

#include "AssetManager.h"
#include "Sprite.h"


IMPLEMENT_COMPONENT(Sprite)


Sprite::Sprite(unsigned int uniqueID)
    : Component(uniqueID, "Sprite") {

    xDimension = 0;
    yDimension = 0;
    xOrigin = 0;
    yOrigin = 0;
    xPos = 0;
    yPos = 0;
}

Sprite::~Sprite() {
    

}

void Sprite::initialize() {


}

void Sprite::update() {


}

void Sprite::render() {

	
}

void Sprite::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    std::string assetName = "";

    FileSystem::Instance().getAttribute(accessor, "xDimension", xDimension);
    FileSystem::Instance().getAttribute(accessor, "yDimension", yDimension);
    FileSystem::Instance().getAttribute(accessor, "xOrigin", xOrigin);
    FileSystem::Instance().getAttribute(accessor, "yOrigin", yOrigin);

    if (FileSystem::Instance().getAttribute(accessor, "Asset", assetName)) {

        // Maintain asset reference count and make texture asset usable
        spriteImagePtr = AssetManager::Instance().getAsset(assetName.c_str());
        spriteImage = (TextureAsset *)spriteImagePtr.lock().get();
    }
}