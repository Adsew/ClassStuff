/*
Student: James Brooks
Class: Game Architecture

File: Component.cpp

Class: Component

Description:
*/


#define DEBUG


#include <iostream>

#include "Component.h"


Component::Component() {

    id = 0;

#ifdef DEBUG
    std::cout << "Component created\n";
#endif // DEBUG
}

Component::Component(int myID) {

    id = myID;

#ifdef DEBUG
    std::cout << "Component created\n";
#endif // DEBUG
}

Component::~Component() {

#ifdef DEBUG
    std::cout << "Component destroyed\n";
#endif // DEBUG
}

// Initialize component for use
void Component::initialize() {

    Object::initialize();

#ifdef DEBUG
    std::cout << "Component initalized\n";
#endif // DEBUG
}

// Cycle update for component
void Component::update() {


}
