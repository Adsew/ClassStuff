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

// Get ID for component as string
int Component::getComponentId() {

    return id;
}

// Cycle update for component
void Component::update() {


}

// Display component to screen
void Component::display() {

    std::cout << "        Component\n";
    std::cout << "        --------------\n";

    std::cout << "        ID: " << id << "\n\n";
}