/*
Student: James Brooks
Class: Game Architecture

File: Bomb.cpp

Class: Bomb

Description: Represents an object that will detonate after a set time.
*/


#include "Core.h"

#include "AnimatedSprite.h"
#include "Terrain.h"
#include "Bomb.h"


IMPLEMENT_COMPONENT(Bomb);


Bomb::Bomb(unsigned int uniqueID) 
    : Component(uniqueID, "Bomb") {

    map = NULL;

    posX = 0;
    posY = 0;

    exploded = false;

    owner = NULL;
}

Bomb::Bomb(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {

    map = NULL;

    posX = 0;
    posY = 0;

    exploded = false;

    owner = NULL;
}

Bomb::~Bomb() {


}

void Bomb::initialize() {


}

void Bomb::update() {

    if (anim != NULL) {
        if (anim->hasPlayedCountTimes()) {

            exploded = true;
        }
    }
}

void Bomb::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}

Component &Bomb::operator=(const Component &comp) {

    const Bomb *orig = (const Bomb *)&comp;

    posX = orig->posX;
    posY = orig->posY;

    return *this;
}

// Reset the bomb to a pre-exploded state
void Bomb::resetBomb() {

    anim = (AnimatedSprite *)gameObject->getComponent("AnimatedSprite");

    if (anim != NULL) {

        anim->resetAnimation();
    }

    exploded = false;
}

// Place the bomb at the given location in the map
void Bomb::placeAtMe(Terrain *terrain, int x, int y) {

    if (terrain != NULL) {

        map = terrain;

        map->placeEntityOnMapNoCollision(gameObject, x, y);
    }
}

// Check if the bomb has exploded and needs deactivation
bool Bomb::isExploded() {

    return exploded;
}
