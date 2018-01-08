/*
Student: James Brooks
Class: Game Architecture

File: EnemyAI.cpp

Class: EnemyAI

Description: Controls the actions the enemies will take.
    They will move randomly and drop bombs.
*/


#include "Core.h"

#include "Terrain.h"
#include "AnimatedSprite.h"
#include "EnemyAI.h"


IMPLEMENT_COMPONENT(EnemyAI);


EnemyAI::EnemyAI(unsigned int uniqueID)
    : Component(uniqueID, "EnemyAI") {

    posX = 0;
    posY = 0;

    bombPlaceInterval = 0;
    bombPlaceChance = 0;
    moveInterval = 0;

    deltaTimeMove = 0;
    deltaTimeBomb = 0;
}

EnemyAI::EnemyAI(unsigned int uniqueID, const char *type) 
    : Component(uniqueID, type) {

    posX = 0;
    posY = 0;

    bombPlaceInterval = 0;
    bombPlaceChance = 0;
    moveInterval = 0;

    deltaTimeMove = 0;
    deltaTimeBomb = 0;
}

EnemyAI::~EnemyAI() {


}

void EnemyAI::initialize() {


}

void EnemyAI::update() {

    if (map != NULL) {
        
        deltaTimeMove += Timer::Instance().getDelta();
        deltaTimeBomb += Timer::Instance().getDelta();

        // Movement update
        if (deltaTimeMove >= moveInterval) {

            AnimatedSprite *anim = (AnimatedSprite *)gameObject->getComponent("AnimatedSprite");
            int direction = rand() % 4;

            deltaTimeMove -= moveInterval;

            // Right
            if (direction == 0) {
                if (map->requestMoveEntity(gameObject->getTransform(), posX, posY, 1, 0)) {

                    posX++;
                    anim->setAnimation(3);
                }
            }
            // Left
            else if (direction == 1) {
                if (map->requestMoveEntity(gameObject->getTransform(), posX, posY, -1, 0)) {

                    posX--;
                    anim->setAnimation(1);
                }
            }
            // Up
            else if (direction == 2) {
                if (map->requestMoveEntity(gameObject->getTransform(), posX, posY, 0, -1)) {

                    posY--;
                    anim->setAnimation(2);
                }
            }
            // Down
            else if (direction == 3) {
                if (map->requestMoveEntity(gameObject->getTransform(), posX, posY, 0, 1)) {

                    posY++;
                    anim->setAnimation(0);
                }
            }
        }

        // Bomb placing update
        if (deltaTimeBomb >= bombPlaceInterval) {

            deltaTimeBomb -= bombPlaceInterval;


        }
    }
}

void EnemyAI::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    FileSystem::Instance().getAttribute(accessor, "bombInterval", bombPlaceInterval);
    FileSystem::Instance().getAttribute(accessor, "bombChance", bombPlaceChance);
    FileSystem::Instance().getAttribute(accessor, "moveInterval", moveInterval);
}

Component &EnemyAI::operator=(const Component &comp) {

    const EnemyAI *orig = (const EnemyAI *)&comp;

    bombPlaceInterval = orig->bombPlaceInterval;
    bombPlaceChance = orig->bombPlaceChance;
    moveInterval = orig->moveInterval;

    return *this;
}

void EnemyAI::setMap(Terrain *m) {

    map = m;
}

void EnemyAI::setPosition(int x, int y) {

    posX = x;
    posY = y;
}
