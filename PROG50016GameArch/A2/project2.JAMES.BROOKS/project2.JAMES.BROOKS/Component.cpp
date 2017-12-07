/*
Student: James Brooks
Class: Game Architecture

File: Component.cpp

Class: Component

Description: A base class for all components that can be added to a game object.
*/


#include "Core.h"

#include "Component.h"


Component::Component(unsigned int uniqueID)
    : Object(uniqueID) {

}

Component::Component(unsigned int uniqueID, const char *compName) 
    : Object(uniqueID) {


}

Component::Component(unsigned int uniqueID, const std::string &compName) 
    : Object(uniqueID) {


}

Component::~Component() {

}

std::string &Component::getName() {

    return name;
}
