/*
Student: James Brooks
Class: Game Architecture

File: InputManager.cpp

Class: InputManager

Description: Manages and refines input received from the user for use elsewhere.
*/


#include "Core.h"

#include "RenderSystem.h"
#include "InputManager.h"


void InputManager::initialize() {

    keyDownState.clear();
    keyPressedState.clear();
    keyReleasedState.clear();

    gameCloseTriggered = false;
}

void InputManager::update() {

    sf::Event windowEvent;

    keyPressedState.clear();
    keyReleasedState.clear();

    while (RenderSystem::Instance().getWindow()->pollEvent(windowEvent)) {

        if (windowEvent.type == sf::Event::Closed) {

            RenderSystem::Instance().getWindow()->close();

            gameCloseTriggered = true;
        }
        else if (windowEvent.type == sf::Event::KeyPressed) {
            
            keyDownState[windowEvent.key.code] = true;
            keyPressedState[windowEvent.key.code] = true;
        }
        else if (windowEvent.type == sf::Event::KeyReleased) {

            keyDownState[windowEvent.key.code] = false;
            keyReleasedState[windowEvent.key.code] = true;
        }
    }
}

// True if key was pressed during this update cycle
bool InputManager::getKeyPressed(const sf::Keyboard::Key &key) {
    
    try {

        return keyPressedState.at(key);
    }
    catch (...) {}

    return false;
}

// True if key was released during this update cycle
bool InputManager::getKeyReleased(const sf::Keyboard::Key &key) {

    try {

        return keyReleasedState.at(key);
    }
    catch (...) {}

    return false;
}

// True if key is held down, false if up
bool InputManager::getKeyDown(const sf::Keyboard::Key &key) {

    try {

        return keyDownState.at(key);
    }
    catch (...) {
        
        keyDownState[key] = false;  // Game wants this key, so we will preemtively create it to avoid exceptions
    }

    return false;
}
