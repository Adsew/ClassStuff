/*
Student: James Brooks
Class: Game Architecture

File: Transform.cpp

Class: Transform

Description: Holds the position, orientation, and scale data for a game object.
*/


#include "Core.h"

#include "Transform.h"


IMPLEMENT_COMPONENT(Transform)


Transform::Transform(unsigned int uniqueID)
    : Component(uniqueID, "Transform") {

    position.x = 0;
    position.y = 0;
    scale.x = 0;
    scale.y = 0;
    rotation = 0;
}

Transform::~Transform() {


}

void Transform::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    FileSystem::Instance().getAttribute(accessor, "position.x", position.x);
    FileSystem::Instance().getAttribute(accessor, "position.y", position.y);
    FileSystem::Instance().getAttribute(accessor, "scale.x", scale.x);
    FileSystem::Instance().getAttribute(accessor, "scale.y", scale.y);
    FileSystem::Instance().getAttribute(accessor, "rotation", rotation);
}

void Transform::initialize() {


}

void Transform::update() {


}
