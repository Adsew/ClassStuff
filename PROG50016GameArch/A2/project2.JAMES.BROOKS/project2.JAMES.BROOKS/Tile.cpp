/*
Student: James Brooks
Class: Game Architecture

File: Tile.cpp

Class: Tile

Description: Component that defines the type of tile in the terrain grid.
Types are: Collidable, Not Collidable
*/

#include "Core.h"

#include "Tile.h"


IMPLEMENT_COMPONENT(Tile);


Tile::Tile(unsigned int uniqueID)
    : Component(uniqueID, "Tile") {

    collidable = false;
    destroyable = false;
}

Tile::Tile(unsigned int uniqueID, const char *type) 
    : Component(uniqueID, type) {

    collidable = false;
    destroyable = false;
}

Tile::~Tile() {


}

void Tile::initialize() {


}

void Tile::update() {


}

void Tile::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    FileSystem::Instance().getAttribute(accessor, "collidable", collidable);
}

Component &Tile::operator=(const Component &comp) {

    const Tile *orig = (const Tile *)&comp;

    collidable = orig->collidable;

    return *this;
}

void Tile::setCollidable(bool c) {

    collidable = c;
}

bool Tile::isCollidable() {

    return collidable;
}

void Tile::setDestructable(bool d) {

    destroyable = d;
}

bool Tile::isDestructable() {

    return destroyable;
}
