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
#include "Transform.h"
#include "AnimatedSprite.h"
#include "PlayerControls.h"


IMPLEMENT_COMPONENT(PlayerControls)


PlayerControls::PlayerControls(unsigned int uniqueID)
    : Component(uniqueID, "PlayerControls") {

    deltaTime = 0;

    map = NULL;
}

PlayerControls::PlayerControls(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {

    deltaTime = 0;

    map = NULL;
}

PlayerControls::~PlayerControls() {


}

void PlayerControls::initialize() {


}

void PlayerControls::update() {

    InputManager &im = InputManager::Instance();
    Transform *trans = gameObject->getTransform();
    AnimatedSprite *anim = (AnimatedSprite *)gameObject->getComponent("AnimatedSprite");

    deltaTime += Timer::Instance().getDelta();

    if (deltaTime >= Timer::Instance().getTargetUpdatesPerSecond()) {

        deltaTime -= Timer::Instance().getTargetUpdatesPerSecond();

        if (trans != NULL &&anim != NULL) {

            // movement
            if (im.getKeyDown(sf::Keyboard::A)) {

                trans->position.x -= 0.5f;
                anim->setAnimation(1);
            }
            if (im.getKeyDown(sf::Keyboard::D)) {

                trans->position.x += 0.5f;
                anim->setAnimation(3);
            }
            if (im.getKeyDown(sf::Keyboard::W)) {

                trans->position.y -= 0.5f;
                anim->setAnimation(2);
            }
            if (im.getKeyDown(sf::Keyboard::S)) {

                trans->position.y += 0.5f;
                anim->setAnimation(0);
            }

            // place bomb button
            if (im.getKeyPressed(sf::Keyboard::Space)) {

                GameObject *go = this->gameObject->clone();
            }

            if (im.getKeyPressed(sf::Keyboard::Escape)) {

                im.exit();
            }
        }
    }
}

void PlayerControls::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}

Component &PlayerControls::operator=(const Component &comp) {

    return *this;
}

void PlayerControls::setMap(Terrain *m) {

    map = m;
}
