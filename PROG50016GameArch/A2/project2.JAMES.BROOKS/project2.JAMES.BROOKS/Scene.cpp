/*
Student: James Brooks
Class: Game Architecture

File: Scene.cpp

Class: Scene

Description: Holds multiple game objects grouped together to make a scene.
Ensures easier management of game objects active at a time.
*/


#include "Core.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "Scene.h"



Scene::Scene(unsigned int id, const char *n) : Object(id) {

    name = n;

    gameObjects.clear();
}


Scene::~Scene() {

    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        (*iter)->destroy();
    }
}

void Scene::initialize() {


}

// Loads a scene file with the same name as the scene
bool Scene::load() {

    std::unique_ptr<FileSystem::FileAccessor> accessor = FileSystem::Instance().useFile(name);

    if (accessor != NULL) {

        if (FileSystem::Instance().traverseToElement(accessor, "Scene")) {
            if (FileSystem::Instance().traverseToElement(accessor, "GameObject")) {

                do {

                    GameObject *newGO = GameObjectManager::Instance().createGameObject();

                    if (newGO != NULL) {

                        newGO->load(accessor);
                    }

                } while (FileSystem::Instance().traverseToSyblingElement(accessor));
            }
        }

        return true;
    }

    return false;
}

// Remove game object from the list of those managed by this scene (does not delete GO)
void Scene::unmanageGameObject(GameObject *go) {

    for (std::list<GameObject *>::iterator iter = gameObjects.begin();
        iter != gameObjects.end();
        iter++) {

        if (*go == *(*iter)) {

            iter = gameObjects.erase(iter);
        }
    }
}
