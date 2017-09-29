/*
Student: James Brooks
Class: Game Architecture

File: Component.cpp

Class: Component

Description:
*/


#include <iostream>

#include "Component.h"


Component::Component(int myID) {

    id = myID;
}

Component::~Component() {


}

// Initialize component for use
void Component::initialize() {


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