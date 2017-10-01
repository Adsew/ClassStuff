/*
Student: James Brooks
Class: Game Architecture

File: Object.cpp

Class: Object

Description: Base class for all objects in the game engine
*/


#include "Object.h"


Object::Object() {

    name = "";
    initialized = false;
}

Object::~Object() {


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


}

// Display object to the screen
void Object::display() {


}