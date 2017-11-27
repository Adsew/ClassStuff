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
    needsDeletion = false;
}

Object::Object(std::string &n) 
    : name(n.c_str()) {

    initialized = false;
    needsDeletion = false;
}

Object::Object(const char *n)
    : name(n) {

    initialized = false;
    needsDeletion = false;
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

// Set object for deletion at a later time by manager
void Object::destroy() {

    needsDeletion = true;
}

// Returns the status of the object if it is to be destroyed
bool Object::getNeedsDeletion() {

    return needsDeletion;
}

// Get name of object
std::string &Object::getName() {

    return name;
}
