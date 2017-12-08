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

    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        delete *iter;
    }

    gameObjects.clear();
}

void GameObjectManager::initialize() {

    uniqueIDCount = 0;
}

void GameObjectManager::update() {

    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        if ((*iter)->pollNeedsDeletion()) {

            delete *iter;
            iter = gameObjects.erase(iter);
        }
        else {

            (*iter)->update();
        }
    }
}

GameObject *GameObjectManager::createGameObject() {

    GameObject *go = new GameObject(uniqueIDCount);
    
    gameObjects.push_back(go);

    uniqueIDCount++;

    return go;
}
