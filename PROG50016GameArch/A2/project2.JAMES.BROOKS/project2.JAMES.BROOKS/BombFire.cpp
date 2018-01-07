/*
Student: James Brooks
Class: Game Architecture

File: BombFire.cpp

Class: BombFire

Description: Spawned by a bomb after it detonates and kills enemies and players it touches.
*/


#include "Core.h"

#include "BombFire.h"


IMPLEMENT_COMPONENT(BombFire);


BombFire::BombFire(unsigned int uniqueID)
    : Component (uniqueID, "BombFire") {


}

BombFire::BombFire(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {


}

BombFire::~BombFire() {


}

void BombFire::initialize() {


}

void BombFire::update() {


}

void BombFire::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}

Component &BombFire::operator=(const Component &comp) {

    const BombFire *orig = (const BombFire *)&comp;

    return *this;
}
