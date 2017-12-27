/*
Student: James Brooks
Class: Game Architecture

File: Sprite.cpp

Class: Sprite

Description: A small image to be rendered to the screen.
*/


#include "Core.h"


#include "Sprite.h"


IMPLEMENT_COMPONENT(Sprite)


Sprite::Sprite(unsigned int uniqueID)
    : Component(uniqueID, "Sprite") {

    xDimension = 0;
    yDimension = 0;
    xOrigin = 0;
    yOrigin = 0;
    xPos = 0;
    yPos = 0;
}

Sprite::~Sprite() {
    

}

void Sprite::initialize() {


}

void Sprite::update() {


}

void Sprite::render() {

	
}
