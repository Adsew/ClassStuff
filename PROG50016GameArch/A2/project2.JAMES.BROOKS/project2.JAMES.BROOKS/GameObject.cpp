/*
Student: James Brooks
Class: Game Architecture

File: GameObject.cpp

Class: GameObject

Description: A standard object to be created into the scene.
*/


#include "Core.h"

#include "GameObject.h"
#include "Component.h"


GameObject::GameObject() {


}

GameObject::~GameObject() {

	auto iter = components.begin();
	
    while (iter != components.end())
	{
		delete (*iter).second;
		++iter;
	}
	components.clear();
}

void GameObject::initialize() {

	Object::initialize();
}

void GameObject::addComponent(Component * component) {

	components.insert(std::pair<std::string, Component*>(component->getComponentId(), component));
}

void GameObject::removeComponent(Component * component) {

	components.erase(component->getComponentId());
}

void GameObject::update() {

	auto iter = components.begin();
	
    while (iter != components.end())
	{
		// update component possibly???
		++iter;
	}
}

