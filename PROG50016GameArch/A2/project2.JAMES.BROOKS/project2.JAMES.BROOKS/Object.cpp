/*
Student: James Brooks
Class: Game Architecture

File: Object.cpp

Class: Object

Description: Base class for most entities persisting in the game world.
*/


#include "Core.h"

#include "Object.h"


Object::Object() {

	std::cout << "Object Created" << std::endl;
}

Object::~Object() {

	std::cout << "Object Destroyed" << std::endl;
}

void Object::initialize() {

	initialized = true;

	std::cout << "Object initialized" << std::endl;
}
