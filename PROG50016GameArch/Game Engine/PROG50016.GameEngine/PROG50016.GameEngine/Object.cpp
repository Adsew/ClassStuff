/*
Student: James Brooks
Class: Game Architecture

File: Object.cpp

Class: Object

Description: Base class for all objects in the game engine
*/


#define DEBUG true


#include <iostream>

#include "Object.h"


Object::Object() {

    name = "";
    initialized = false;

#ifdef DEBUG
    std::cout << "Object created\n";
#endif // DEBUG

}

Object::~Object() {

#ifdef DEBUG
    std::cout << "Object destroyed\n";
#endif // DEBUG
}

// Check object initialized correctly and ise usable
bool Object::isInitialized() {

    return initialized;
}

// Get name of object
std::string Object::getName() {

    return name;
}

// Initialize object to a usable state
void Object::initialize() {

    initialized = true;

#ifdef DEBUG
    std::cout << "Object initialized\n";
#endif // DEBUG
}

// Display object to the screen
void Object::display() {


}
