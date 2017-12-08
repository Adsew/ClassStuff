/*
Student: James Brooks
Class: Game Architecture

File: Sprite.cpp

Class: Sprite

Description: A small image to be rendered to the screen.
*/


#include "Core.h"

#include "ComponentManager.h"
#include "Sprite.h"


void Sprite::generateType() {

    ComponentManager::Instance().addComponentType<Sprite>("Sprite");
}

Sprite::Sprite(unsigned int uniqueID)
    : Component(uniqueID, "Sprite") {

	
}

Sprite::~Sprite() {
    

}

void Sprite::initialize() {


}

void Sprite::update() {


}

void Sprite::render() {

	
}
