/*
Student: James Brooks
Class: Game Architecture

File: Bomb.cpp

Class: Bomb

Description: Represents an object that will detonate after a set time.
*/


#include "Core.h"

#include "GameObjectManager.h"
#include "AnimatedSprite.h"
#include "Terrain.h"
#include "BombFire.h"
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

            explode();
        }
    }
}

void Bomb::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}

Component &Bomb::operator=(const Component &comp) {

    const Bomb *orig = (const Bomb *)&comp;

    posX = orig->posX;
    posY = orig->posY;

    firePoolID = orig->firePoolID;

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

        posX = x;
        posY = y;
    }
}

// Called when the bomb explodes after the animation finishes
void Bomb::explode() {

    exploded = true;

    if (map != NULL) {

        // Create 9 fire sprites from the bombs position
        for (int i = 0; i < 9; i++) {

            GameObject *fire = GameObjectManager::Instance().requestFromPool(firePoolID);

            if (fire != NULL) {

                BombFire *fireScript = (BombFire *)fire->getComponent("BombFire");
                int x = 0, y = 0;
                
                if (i == 0) {

                    x = posX;
                    y = posY;
                }
                // Up fire
                else if (i > 0 && i < 3) {

                    x = posX;
                    y = posY - i;
                }
                // Down fire
                else if (i > 2 && i < 5) {

                    x = posX;
                    y = posY + i - 2;
                }
                // Left fire
                else if (i > 4 && i < 7) {

                    x = posX - i + 4;
                    y = posY;
                }
                // Right fire
                else if (i > 6 && i < 9) {

                    x = posX + i - 6;
                    y = posY;
                }

                if (fireScript != NULL) {

                    fireScript->setMap(map, x, y);

                    map->placeEntityOnMapNoCollision(fire, x, y);
                }
            }
        }
    }

    gameObject->destroy();
}

// Set the fire pool ID to be used when exploding
void Bomb::setFirePoolID(unsigned int fID) {

    firePoolID = fID;
}