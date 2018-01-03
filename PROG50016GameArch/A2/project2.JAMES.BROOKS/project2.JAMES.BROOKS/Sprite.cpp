/*
Student: James Brooks
Class: Game Architecture

File: Sprite.cpp

Class: Sprite

Description: A small image to be rendered to the screen.
*/


#include "Core.h"

#include "Transform.h"
#include "RenderSystem.h"
#include "AssetManager.h"
#include "TextureAsset.h"
#include "Sprite.h"


IMPLEMENT_COMPONENT(Sprite)


Sprite::Sprite(unsigned int uniqueID)
    : Component(uniqueID, "Sprite") {
    
}

Sprite::Sprite(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {

}

Sprite::~Sprite() {
    

}

void Sprite::initialize() {


}

void Sprite::update() {
    
    Transform *trans = (Transform *)gameObject->getComponent("Transform");
    
    if (trans != NULL) {

        sprite.setPosition(trans->position);
        sprite.setRotation(trans->rotation);
        sprite.setScale(trans->scale);
    }
}

void Sprite::render() {
    
    RenderSystem::Instance().getWindow()->draw(sprite);
}

void Sprite::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    std::string assetName = "";

    FileSystem::Instance().getAttribute(accessor, "width", spriteRect.width);
    FileSystem::Instance().getAttribute(accessor, "height", spriteRect.height);
    FileSystem::Instance().getAttribute(accessor, "xOrigin", spriteRect.left);
    FileSystem::Instance().getAttribute(accessor, "yOrigin", spriteRect.top);

    if (FileSystem::Instance().getAttribute(accessor, "Asset", assetName)) {

        TextureAsset *temp = NULL;

        // Maintain asset reference count and make texture asset remains usable
        spriteImagePtr = AssetManager::Instance().getAsset(assetName.c_str());

        temp = (TextureAsset *)spriteImagePtr.get();

        if (temp != NULL) {

            sprite.setTexture(*(temp->getTexture()));
            sprite.setTextureRect(spriteRect);
        }
        else {

            DEBUG_LOG("Sprite: Unable to retrieve texture asset for " << assetName.c_str() << ".");
        }
    }
}

void Sprite::setRectangle(int width, int height, int x, int y) {

    spriteRect.width = width;
    spriteRect.height = height;
    spriteRect.left = x;
    spriteRect.top = y;

    sprite.setTextureRect(spriteRect);
}

void Sprite::setTextureAsset(const char *assetName) {

    TextureAsset *temp = NULL;

    std::shared_ptr<Asset> tempAsset = AssetManager::Instance().getAsset(assetName);

    temp = (TextureAsset *)tempAsset.get();

    if (temp != NULL) {

        spriteImagePtr = tempAsset;

        sprite.setTexture(*(temp->getTexture()));
    }
    else {

        DEBUG_LOG("Sprite: Unable to retrieve texture asset for " << assetName << ".");
    }
}
