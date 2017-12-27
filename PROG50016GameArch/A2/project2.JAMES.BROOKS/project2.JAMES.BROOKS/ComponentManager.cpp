/*
Student: James Brooks
Class: Game Architecture

File: ComponentManager.cpp

Class: ComponentManager

Description: Maintains the memory and functionality of all components currently loaded.
*/


#include "Core.h"

#include "Component.h"
#include "ComponentManager.h"


ComponentManager::~ComponentManager() {

    for (std::list<Component *>::iterator iter = components.begin();
        iter != components.end();
        iter++) {

        delete *iter;
    }

    components.clear();
}

void ComponentManager::initialize() {
    
}

void ComponentManager::update() {

    for (std::list<Component *>::iterator iter = components.begin();
        iter != components.end();
        iter++) {

        if ((*iter)->pollNeedsDeletion()) {

            delete *iter;
            iter = components.erase(iter);
        }
        else {

            (*iter)->update();
        }
    }
}

void ComponentManager::addComponentType(const char *name, std::function<Component *(unsigned int)> creationFunc) {

    createComponent[name] = creationFunc;
}
