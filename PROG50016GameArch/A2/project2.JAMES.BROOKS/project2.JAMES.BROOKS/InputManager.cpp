/*
Student: James Brooks
Class: Game Architecture

File: InputManager.cpp

Class: InputManager

Description: Manages and refines input received from the user for use elsewhere.
*/


#include "Core.h"

#include "Timer.h"
#include "RenderSystem.h"
#include "InputManager.h"


void InputManager::initialize() {

    keyDownState.clear();
    keyPressedState.clear();
    keyReleasedState.clear();

    deltaTime = 0;

    gameCloseTriggered = false;
}

void InputManager::clean() {


}

void InputManager::update() {

    sf::Event windowEvent;

    deltaTime += Timer::Instance().getDelta();

    if (deltaTime >= Timer::Instance().getTargetUpdatesPerSecond()) {

        deltaTime -= Timer::Instance().getTargetUpdatesPerSecond();

        keyPressedState.clear();
        keyReleasedState.clear();

        while (RenderSystem::Instance().getWindow()->pollEvent(windowEvent)) {

            if (windowEvent.type == sf::Event::Closed) {

                exit();
            }
            else if (windowEvent.type == sf::Event::KeyPressed) {

                if (keyDownState.find(windowEvent.key.code) != keyDownState.end()) {

                    // Pushed before, but was not pushed last update
                    if (!keyDownState[windowEvent.key.code]) {

                        keyDownState[windowEvent.key.code] = true;
                        keyPressedState[windowEvent.key.code] = true;
                    }
                }
                // Never been pushed before, so create and set true
                else {

                    keyDownState[windowEvent.key.code] = true;
                    keyPressedState[windowEvent.key.code] = true;
                }
            }
            else if (windowEvent.type == sf::Event::KeyReleased) {

                keyDownState[windowEvent.key.code] = false;
                keyReleasedState[windowEvent.key.code] = true;
            }
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
        
        keyDownState[key] = false;  // Game wants this key, so we will pre-emtively create it to avoid exceptions
    }

    return false;
}

// Sets the game exit flag to true (should be moved elsewhere, not sure where though)
void InputManager::exit() {

    gameCloseTriggered = true;
}