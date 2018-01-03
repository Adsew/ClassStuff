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
}

Tile::Tile(unsigned int uniqueID, const char *type) 
    : Component(uniqueID, type) {

    collidable = false;
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

void Tile::setCollidable(bool c) {

    collidable = c;
}

bool Tile::isCollidable() {

    return collidable;
}