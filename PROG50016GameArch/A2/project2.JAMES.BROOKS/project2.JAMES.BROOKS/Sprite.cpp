/*
Student: James Brooks
Class: Game Architecture

File: Sprite.cpp

Class: Sprite

Description: A small image to be rendered to the screen.
*/


#include "Core.h"

#include "RenderSystem.h"
#include "AssetManager.h"
#include "TextureAsset.h"
#include "Sprite.h"


IMPLEMENT_COMPONENT(Sprite)


Sprite::Sprite(unsigned int uniqueID)
    : Component(uniqueID, "Sprite") {
    
}

Sprite::~Sprite() {
    

}

void Sprite::initialize() {


}

void Sprite::update() {
    
    /*if (InputManager::Instance().getKeyDown(sf::Keyboard::A)) {

        x--;
    }
    if (InputManager::Instance().getKeyDown(sf::Keyboard::D)) {

        x++;
    }
    if (InputManager::Instance().getKeyDown(sf::Keyboard::W)) {

        y--;
    }
    if (InputManager::Instance().getKeyDown(sf::Keyboard::S)) {

        y++;
    }

    sprite.setPosition(x, y);*/
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