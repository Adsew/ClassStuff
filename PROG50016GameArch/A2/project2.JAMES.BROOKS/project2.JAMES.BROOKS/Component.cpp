/*
Student: James Brooks
Class: Game Architecture

File: Component.cpp

Class: Component

Description: A base class for all components that can be added to a game object.
*/


#include "Core.h"

#include "Component.h"


Component::Component(unsigned int uniqueID, const char *compType) 
    : Object(uniqueID), type(compType) {

    gameObject = NULL;
}

Component::Component(unsigned int uniqueID, const std::string &compType) 
    : Object(uniqueID), type(compType) {

    gameObject = NULL;
}

Component::~Component() {

}

GameObject * const Component::getGameObject() {

    return gameObject;
}
