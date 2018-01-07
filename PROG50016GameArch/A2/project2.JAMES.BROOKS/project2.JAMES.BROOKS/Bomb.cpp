/*
Student: James Brooks
Class: Game Architecture

File: Bomb.cpp

Class: Bomb

Description: Represents an object that will detonate after a set time.
*/


#include "Core.h"

#include "Bomb.h"


IMPLEMENT_COMPONENT(Bomb);


Bomb::Bomb(unsigned int uniqueID) 
    : Component(uniqueID, "Bomb") {


}

Bomb::Bomb(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {


}

Bomb::~Bomb() {


}

void Bomb::initialize() {


}

void Bomb::update() {


}

void Bomb::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}

Component &Bomb::operator=(const Component &comp) {

    const Bomb *orig = (const Bomb *)&comp;

    return *this;
}
