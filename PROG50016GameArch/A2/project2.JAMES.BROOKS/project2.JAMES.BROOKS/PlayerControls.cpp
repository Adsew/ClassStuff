/*
Student: James Brooks
Class: Game Architecture

File: PlayerControls.cpp

Class: PlayerControls

Description: Component allowing input from the keyboard to move the player accordingly.
*/


#include "Core.h"

#include <SFML/Window/Keyboard.hpp>

#include "Timer.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "Transform.h"
#include "Bomb.h"
#include "Terrain.h"
#include "Transform.h"
#include "AnimatedSprite.h"
#include "PlayerControls.h"


IMPLEMENT_COMPONENT(PlayerControls)


PlayerControls::PlayerControls(unsigned int uniqueID)
    : Component(uniqueID, "PlayerControls") {

    deltaTimeInput = 0;
    deltaTimeBomb = 0;

    map = NULL;
    posX = 0;
    posY = 0;

    bombInterval = 0;
}

PlayerControls::PlayerControls(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {

    deltaTimeInput = 0;
    deltaTimeBomb = 0;

    map = NULL;
    posX = 0;
    posY = 0;

    bombInterval = 0;
}

PlayerControls::~PlayerControls() {


}

void PlayerControls::initialize() {


}

void PlayerControls::update() {

    InputManager &im = InputManager::Instance();
    Transform *trans = gameObject->getTransform();
    AnimatedSprite *anim = (AnimatedSprite *)gameObject->getComponent("AnimatedSprite");

    deltaTimeInput += Timer::Instance().getDelta();
    deltaTimeBomb += Timer::Instance().getDelta();

    if (deltaTimeInput >= Timer::Instance().getTargetUpdatesPerSecond()) {

        deltaTimeInput -= Timer::Instance().getTargetUpdatesPerSecond();

        // Check for exit first
        if (im.getKeyPressed(sf::Keyboard::Escape)) {

            im.exit();
        }
        else if (trans != NULL && anim != NULL && map != NULL) {

            // movement
            if (im.getKeyDown(sf::Keyboard::A)) {

                if (map->requestMoveEntity(trans, posX, posY, -1, 0)) {

                    posX--;
                }
                
                anim->setAnimation(1);
            }
            if (im.getKeyDown(sf::Keyboard::D)) {

                if (map->requestMoveEntity(trans, posX, posY, 1, 0)) {

                    posX++;
                }

                anim->setAnimation(3);
            }
            if (im.getKeyDown(sf::Keyboard::W)) {

                if (map->requestMoveEntity(trans, posX, posY, 0, -1)) {

                    posY--;
                }

                anim->setAnimation(2);
            }
            if (im.getKeyDown(sf::Keyboard::S)) {

                if (map->requestMoveEntity(trans, posX, posY, 0, 1)) {

                    posY++;
                }

                anim->setAnimation(0);
            }

            // place bomb button
            if (im.getKeyPressed(sf::Keyboard::Space)
                && deltaTimeBomb >= bombInterval) {

                deltaTimeBomb = 0;

                GameObject *bomb = GameObjectManager::Instance().requestFromPool(bombPoolID);

                if (bomb != NULL) {

                    Bomb *bombComp = (Bomb *)bomb->getComponent("Bomb");

                    if (bombComp != NULL) {

                        bombComp->owner = gameObject;
                        bombComp->resetBomb();
                        bombComp->placeAtMe(map, posX, posY);
                    }

                    activeBombs.push_back(bomb);
                }
            }
        }

        // Return exploded bombs to pool
        std::list<GameObject *>::iterator iter = activeBombs.begin();

        while (iter != activeBombs.end()) {

            Bomb *b = (Bomb *)(*iter)->getComponent("Bomb");

            if (b != NULL) {
                if (b->isExploded()) {

                    GameObjectManager::Instance().returnToPool(bombPoolID, *iter);

                    iter = activeBombs.erase(iter);
                }
                else {

                    iter++;
                }
            }
            else {

                iter++;
            }
        }
    }
}

void PlayerControls::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    FileSystem::Instance().getAttribute(accessor, "bombInterval", bombInterval);
}

Component &PlayerControls::operator=(const Component &comp) {

    return *this;
}

void PlayerControls::setMap(Terrain *m) {

    map = m;
}

void PlayerControls::setPosition(int x, int y) {

    posX = x;
    posY = y;
}

void PlayerControls::setBombPool(unsigned int id) {

    bombPoolID = id;
}
