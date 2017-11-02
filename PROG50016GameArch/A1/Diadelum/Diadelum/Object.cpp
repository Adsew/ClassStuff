/*
Student: James Brooks
Class: Game Architecture

File: Object.cpp

Class: Object

Description: Base class for all objects in the game engine
*/


#include <iostream>

#include "Object.h"


Object::Object() {

    name = "";
    initialized = false;
}

Object::Object(std::string &n) {

    name = n;
    initialized = false;
}

Object::~Object() {


}

// Initialize object to a usable state
void Object::initialize() {

    initialized = true;
}

// Check object initialized correctly and ise usable
bool Object::isInitialized() {

    return initialized;
}

// Get name of object
std::string &Object::getName() {

    return name;
}
