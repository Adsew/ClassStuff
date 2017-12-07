/*
Student: James Brooks
Class: Game Architecture

File: GameObject.cpp

Class: GameObject

Description: A standard object to be created into the scene.
*/


#include "Core.h"

#include "GameObject.h"
#include "Component.h"


GameObject::GameObject(unsigned int uniqueID)
    : Object(uniqueID) {

    name = "New Game Object";
}

GameObject::GameObject(unsigned int uniqueID, const char *goName)
    : Object(uniqueID) {

    name = goName;
}

GameObject::GameObject(unsigned int uniqueID, const std::string &goName)
    : Object(uniqueID) {

    name = goName.c_str();
}

GameObject::~GameObject() {

    for (std::map<std::string, Component *>::iterator iter = components.begin();
        iter != components.end();
        iter++) {

        (*iter).second->destroy();
    }

	components.clear();
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
