/*
Student: James Brooks
Class: Game Architecture

File: GameObjectManager.cpp

Class: GameObjectManager

Description: Maintains the memory and funcitonality of all game objects currently loaded.
*/


#include "Core.h"

#include "GameObject.h"
#include "GameObjectManager.h"


GameObjectManager::~GameObjectManager() {

    for (std::list<GameObject *>::iterator iter = recentlyCreated.begin();
        iter != recentlyCreated.end();
        iter++) {

        delete *iter;
    }

    recentlyCreated.clear();

    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        delete *iter;
    }

    gameObjects.clear();
}

void GameObjectManager::initialize() {

    Object::initializeIDs();
}

void GameObjectManager::clean() {

    for (std::list<GameObject *>::iterator iter = recentlyCreated.begin();
        iter != recentlyCreated.end();
        iter++) {

        delete *iter;
    }

    recentlyCreated.clear();

    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        delete *iter;
    }

    gameObjects.clear();
}

void GameObjectManager::update() {

    // Add new gameobjects to this cycle update
    for (std::list<GameObject *>::iterator iter = recentlyCreated.begin();
        iter != recentlyCreated.end();
        iter++) {

        gameObjects.push_back(*iter);
    }

    recentlyCreated.clear();

    // Deletion pass
    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        if ((*iter)->pollNeedsDeletion()) {

            delete *iter;
            iter = gameObjects.erase(iter);
        }
    }

    // Normal update after
    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        if ((*iter)->active) {

            (*iter)->update();
        }
    }
}

GameObject *GameObjectManager::createGameObject() {

    GameObject *go = new GameObject(Object::generateID());
    
    recentlyCreated.push_back(go);

    return go;
}
