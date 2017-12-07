/*
Student: James Brooks
Class: Game Architecture

File: Object.cpp

Class: Object

Description: Base class for most entities persisting in the game world.
*/


#include "Core.h"

#include "Object.h"


Object::Object(unsigned int uniqueID) {

    id = uniqueID;

    initialized = false;
    needsDeletion = false;
}

Object::~Object() {}

// Return true if id's are the same
bool Object::operator==(const Object &obj) {

    if (id == obj.id) {

        return true;
    }

    return false;
}

// Return true if object has been initialized
bool Object::isInitialized() {
    
    return initialized;
}

// Set an object to be deleted by the manager
void Object::destroy() {

    needsDeletion = true;
}

// Check if object is set for deletion
bool Object::pollNeedsDeletion() {

    return needsDeletion;
}
