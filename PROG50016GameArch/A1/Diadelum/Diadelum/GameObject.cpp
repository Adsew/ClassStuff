/*
Student: James Brooks
Class: Game Architecture

File: GameObject.cpp

Class: GameObject

Description: A game object to be used to represent objects within the game world.
*/


#include "GameObject.h"


GameObject::GameObject()
    : Object() {

    id = -1;
    
    description = "";

    inUse = false;
    numUses = 1;

    worksWithID = -1;
    createsID = -1;
    locationToUnlock = "";
    onUseMsg = "";
    inZoneMsg = "";
}

GameObject::GameObject(int idNum, std::string &n) 
    : Object(n){

    id = idNum;
    
    description = "";

    inUse = false;
    numUses = 1;

    worksWithID = -1;
    createsID = -1;
    locationToUnlock = "";
    onUseMsg = "";
}

GameObject::~GameObject() {

    
}

// Cycle update for game object
void GameObject::update() {
    

}

std::string GameObject::unlockLocation() {

    if (inUse) {

        return locationToUnlock;
    }
    
    return "";
}

int GameObject::createItem() {

    if (inUse) {

        return createsID;
    }

    return -1;
}

    // Accessors

int GameObject::getID() {

    return id;
}

void GameObject::setDescription(std::string &desc) {

    description = desc;
}

void GameObject::setDescription(const char *desc) {

    description = desc;
}

void GameObject::setInUse(bool b) {

    inUse = b;
}

bool GameObject::getInUse() {

    return inUse;
}

void GameObject::setNumUses(int n) {

    numUses = n;
}

int GameObject::getNumUses() {

    return numUses;
}

void GameObject::setWorksWithID(int otherItemID) {

    worksWithID = otherItemID;
}

int GameObject::getWorksWithID() {

    return worksWithID;
}

void GameObject::setCreatesID(int itemToCreate) {

    createsID = itemToCreate;
}

void GameObject::setLocationToUnlock(std::string &loc) {

    locationToUnlock = loc;
}

void GameObject::setLocationToUnlock(const char *loc) {

    locationToUnlock = loc;
}

void GameObject::setOnUseMsg(std::string &msgWhenUsed) {

    onUseMsg = msgWhenUsed;
}

void GameObject::setOnUseMsg(const char *msgWhenUsed) {

    onUseMsg = msgWhenUsed;
}

void GameObject::setInZoneMsg(std::string &msgInZone) {

    inZoneMsg = msgInZone;
}

void GameObject::setInZoneMsg(const char *msgInZone) {

    inZoneMsg = msgInZone;
}

std::string &GameObject::getInZoneMsg() {

    return inZoneMsg;
}
