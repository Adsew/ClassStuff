/*
Student: James Brooks
Class: Game Architecture

File: PlayerControls.cpp

Class: PlayerControls

Description: Component allowing input from the keyboard to move the player accordingly.
*/


#include "Core.h"

#include <SFML/Window/Keyboard.hpp>

#include "InputManager.h"
#include "Transform.h"
#include "AnimatedSprite.h"
#include "PlayerControls.h"


IMPLEMENT_COMPONENT(PlayerControls)


PlayerControls::PlayerControls(unsigned int uniqueID)
    : Component(uniqueID, "PlayerControls") {


}


PlayerControls::~PlayerControls() {


}

void PlayerControls::initialize() {


}

void PlayerControls::update() {

    InputManager &im = InputManager::Instance();
    Transform *trans = (Transform *)gameObject->getComponent("Transform");
    AnimatedSprite *anim = (AnimatedSprite *)gameObject->getComponent("AnimatedSprite");

    if (trans != NULL &&anim != NULL) {

        // movement
        if (im.getKeyDown(sf::Keyboard::A)) {

            trans->position.x -= 0.1f;
            anim->setAnimation(0);
        }
        if (im.getKeyDown(sf::Keyboard::D)) {

            trans->position.x += 0.1f;
            anim->setAnimation(1);
        }
        if (im.getKeyDown(sf::Keyboard::W)) {

            trans->position.y -= 0.1f;
            anim->setAnimation(2);
        }
        if (im.getKeyDown(sf::Keyboard::S)) {

            trans->position.y += 0.1f;
            anim->setAnimation(3);
        }

        // place bomb
        if (im.getKeyDown(sf::Keyboard::Space)) {

            
        }

        if (im.getKeyDown(sf::Keyboard::Escape)) {

            im.exit();
        }
    }
}

void PlayerControls::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}
