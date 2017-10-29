/*
Student: James Brooks
Class: Game Architecture

File: GameObject.cpp

Class: GameObject

Description: A game object to be used to represent objects within the game world.
*/


#include <iostream>

#include "Component.h"
#include "GameObject.h"


GameObject::GameObject()
    : Object() {


}

GameObject::GameObject(std::string &n) 
    : Object(n){


}

GameObject::~GameObject() {

    std::map<std::string, Component *>::iterator iter = components.begin();

    for (iter = components.begin(); iter != components.end(); iter++) {

        //delete (*iter);
    }
}

// Add component to this game object
void GameObject::addComponent(Component *comp) {

    if (comp != NULL) {

        components.insert(std::pair<std::string, Component *>(comp->getComponentId, comp));
    }
}

// Remove a component, if exists, from game object
void GameObject::removeComponent(Component *comp) {

    /*if (comp != NULL) {

        std::list<Component *>::iterator iter;

        for (iter = components.begin(); iter != components.end(); iter++) {

            if ((*iter)->getComponentId() == comp->getComponentId()) {

                delete *iter;

                iter = components.erase(iter);

                break;
            }
        }
    }*/
}

// Cycle update for game object
void GameObject::update() {
    
    std::map<std::string, Component *>::iterator iter = components.begin();

    for (iter = components.begin(); iter != components.end(); iter++) {

        // update stuff get ocmponent part of pair
        //(*iter)->update();
    }
}
