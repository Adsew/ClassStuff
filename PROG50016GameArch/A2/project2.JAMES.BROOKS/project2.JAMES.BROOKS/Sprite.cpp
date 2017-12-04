/*
Student: James Brooks
Class: Game Architecture

File: Sprite.h

Class: Sprite

Description: A small image to be rendered to the screen.
*/


#include "Sprite.h"


Sprite::Sprite() {

	std::cout << "Sprite Created" << std::endl;
}

Sprite::~Sprite() {

	std::cout << "Sprite Destroyed" << std::endl;
}

void Sprite::initialize() {

	Component::initialize();

	std::cout << "Sprite initialized" << std::endl;
}

void Sprite::render() {

	// Render
}
