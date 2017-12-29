/*
Student: James Brooks
Class: Game Architecture

File: GameObject.cpp

Class: GameObject

Description: A standard object to be created into the scene.
*/


#include "Core.h"

#include "Scene.h"
#include "Component.h"
#include "ComponentManager.h"
#include "GameObject.h"


GameObject::GameObject(unsigned int uniqueID)
    : Object(uniqueID) {

    scene = NULL;
    name = "New Game Object";
}

GameObject::GameObject(unsigned int uniqueID, const char *goName)
    : Object(uniqueID) {

    scene = NULL;
    name = goName;
}

GameObject::GameObject(unsigned int uniqueID, const std::string &goName)
    : Object(uniqueID) {

    scene = NULL;
    name = goName.c_str();
}

GameObject::~GameObject() {

    for (std::map<std::string, Component *>::iterator iter = components.begin();
        iter != components.end();
        iter++) {

        (*iter).second->destroy();
    }

	components.clear();

    if (scene != NULL) {

        scene->unmanageGameObject(this);
    }
}

void GameObject::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    FileSystem::Instance().getAttribute(accessor, "name", name);

    // Load any components under the game object
    if (FileSystem::Instance().traverseToElement(accessor, "Components")) {
        if (FileSystem::Instance().traverseToChildElement(accessor)) {

            Component *tempComp = NULL;
            std::string type = "";

            do {
                FileSystem::Instance().getAttribute(accessor, "type", type);

                tempComp = ComponentManager::Instance().createComponent(type.c_str());

                if (tempComp != NULL) {

                    tempComp->load(accessor);
                }

                addComponent(tempComp);

            } while (FileSystem::Instance().traverseToSyblingElement(accessor));

            FileSystem::Instance().traverseToParentElement(accessor);
        }
    }
}

void GameObject::initialize() {

    
}

void GameObject::addComponent(Component * component) {

    if (component != NULL) {

        components[component->getName()] = component;
    }
}

void GameObject::removeComponent(Component * component) {

    if (component != NULL) {

        std::map<std::string, Component *>::iterator iter = components.find(component->getName());

        if (iter != components.end()) {

            (*iter).second->destroy();
            components.erase(iter);
        }
    }
}

void GameObject::update() {

    for (std::map<std::string, Component *>::iterator iter = components.begin();
        iter != components.end();
        iter++) {

        (*iter).second->update();
    }
}


    /* Gets/Sets */

void GameObject::setName(const char *newName) {

    name = newName;
}

void GameObject::setName(const std::string &newName) {

    this->setName(newName.c_str());
}

std::string &GameObject::getName() {

    return name;
}
