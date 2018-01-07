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

    poolIDCount = 0;
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

    /* Object Pool Functions */

// Creates a pool of the given game object, returns id to access pool
// Does not take responsability for the sample game objects
// Returns -1 on error
unsigned int GameObjectManager::createObjectPool(GameObject *sample, const unsigned int amount) {

    if (sample != NULL) {

        objectPool[poolIDCount].resize(amount);
        objectPoolInUseMap[poolIDCount].resize(amount);

        for (int i = 0; i < amount; i++) {

            objectPool[poolIDCount][i] = sample->clone();
            objectPool[poolIDCount][i]->setActive(false);

            objectPoolInUseMap[poolIDCount][i] = false;
        }

        poolIDCount++;

        return poolIDCount - 1;
    }

    return -1;
}

// Request a game object from the pool
// NULL if none available or pool doesn't exist
GameObject *GameObjectManager::requestFromPool(const unsigned int id) {

    if (objectPool.find(id) != objectPool.end()) {

        for (int i = 0; i < objectPool[id].size(); i++) {

            if (!objectPoolInUseMap[id][i]) {

                objectPoolInUseMap[id][i] = true;

                objectPool[id][i]->setActive(true);

                return objectPool[id][i];
            }
        }
    }
}

// Return an object to the pool for later use
void GameObjectManager::returnToPool(const unsigned int id, GameObject *object) {

    if (objectPool.find(id) != objectPool.end()) {

        for (int i = 0; i < objectPool[id].size(); i++) {

            // Check if pointer is in the pool
            if (objectPool[id][i] == object) {

                objectPoolInUseMap[id][i] = false;

                objectPool[id][i]->setActive(false);
            }
        }
    }
}

// Dispose of the object pool, deleting all objects in the pool
void GameObjectManager::destroyObjectPool(const unsigned int id) {

    if (objectPool.find(id) != objectPool.end()) {

        // Delete all objects in the pool
        for (int i = 0; i < objectPool[id].size(); i++) {

            objectPool[id][i]->destroy();
        }

        objectPool[id].clear();

        objectPool.erase(objectPool.find(id));
        objectPoolInUseMap.erase(objectPoolInUseMap.find(id));
    }
}
