/*
Student: James Brooks
Class: Game Architecture

File: Component.cpp

Class: Component

Description: A base class for all components that can be added to a game object.
*/


#include "Core.h"

#include "Component.h"


Component::Component() {

	std::cout << "Component Created" << std::endl;
}

Component::~Component() {

	std::cout << "Component Destroyed" << std::endl;
}

void Component::initialize() {

	Object::initialize();

	std::cout << "Component initialized" << std::endl;
}
