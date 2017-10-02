/*
Student: James Brooks
Class: Game Architecture

File: GameObjectManager.cpp

Class: GameObjectManager

Description: Manages list of game objects in a given scene
*/


#include <iostream>

#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() {


}

GameObjectManager::~GameObjectManager() {

    std::list<GameObject *>::iterator iter;

    for (iter = gameObjects.begin(); iter != gameObjects.end();) {

        delete *iter;

        iter = gameObjects.erase(iter);
    }
}

// Add game object to the manager
void GameObjectManager::addGameObject(GameObject *go) {

    if (go != NULL) {

        gameObjects.push_back(go);
    }
}

// Remove game object from the manager
void GameObjectManager::removeGameObject(GameObject *go) {

    if (go != NULL) {

        std::list<GameObject *>::iterator iter;

        for (iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {

            if ((*iter)->getName() == go->getName()) {

                delete *iter;

                iter = gameObjects.erase(iter);

                break;
            }
        }
    }
}

// Initialize manager to usable status
void GameObjectManager::initialize() {


}

// Cycle update from manager
void GameObjectManager::update() {

    std::list<GameObject *>::iterator iter;

    for (iter = gameObjects.begin(); iter != gameObjects.end(); ++iter) {

        (*iter)->update();
    }
}

// Display game objects to the screen
void GameObjectManager::display() {

    std::list<GameObject *>::iterator iter;

    std::cout << "Game Manager\n";
    std::cout << "---------------------\n";

    for (iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {

        (*iter)->display();
    }
}
