/*
Student: James Brooks
Class: Game Architecture

File: GameObject.cpp

Class: GameObject

Description: A game object to be used to represent objects within the game world.
*/


#include <iostream>

#include "GameObject.h"


GameObject::GameObject() {

    name = "Game Object";
}

GameObject::GameObject(std::string n) {

    name = n;
}

GameObject::~GameObject() {

    std::list<Component *>::iterator iter;

    for (iter = components.begin(); iter != components.end();) {

        delete *iter;

        iter = components.erase(iter);
    }
}

// Get name of the game object
std::string GameObject::getName() {

    return name;
}

// Add component to this game object
void GameObject::addComponent(Component *comp) {

    if (comp != NULL) {

        components.push_back(comp);
    }
}

// Remove a component, if exists, from game object
void GameObject::removeComponent(Component *comp) {

    if (comp != NULL) {

        std::list<Component *>::iterator iter;

        for (iter = components.begin(); iter != components.end(); iter++) {

            if ((*iter)->getComponentId() == comp->getComponentId()) {

                delete *iter;

                iter = components.erase(iter);

                break;
            }
        }
    }
}

// Cycle update for game object
void GameObject::update() {

    std::list<Component *>::iterator iter;

    for (iter = components.begin(); iter != components.end(); ++iter) {

        (*iter)->update();
    }
}

// Display game object to screen
void GameObject::display() {

    std::list<Component *>::iterator iter;

    std::cout << "    Game Object\n";
    std::cout << "    -----------------\n";

    std::cout << "    Name: " << name << "\n\n";

    for (iter = components.begin(); iter != components.end(); ++iter) {

        (*iter)->display();
    }
}