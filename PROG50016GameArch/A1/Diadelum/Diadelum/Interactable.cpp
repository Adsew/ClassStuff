/*
Student: James Brooks
Class: Game Architecture

File: Interactable.cpp

Class: Interactable

Description: Represents something in the environment that can be
interacted with.
*/


#include "Interactable.h"


Interactable::Interactable(int idNum, std::string n)
    : GameObject(idNum, n) {

    locationToUnlock = "";
}


Interactable::~Interactable() {


}

std::string Interactable::use() {

    // Can be used solo
    if (worksWithID == 0) {

        inUse = true;
        numUses--;

        // If less than 0 means unlimted uses
        if (numUses == 0) {

            needsDeletion = true;
        }
        
        return onUseMsg;
    }

    return "I can't do anything with the " + name + ".";
}

std::string Interactable::useWith(GameObject *go) {

    if (go->getID() == worksWithID) {

        inUse = true;

        numUses--;
        go->setNumUses(go->getNumUses() - 1);

        // If less than 0 means unlimted uses
        if (numUses == 0) {

            needsDeletion = true;
        }
        if (go->getNumUses() == 0) {

            go->setNeedsDeletion(true);
        }

        return onUseMsg;
    }
    else if (go->getWorksWithID() == id) {

        return go->useWith(this);
    }

    return "The " + go->getName() + " has no affect on the " + name + ".";
}

std::string Interactable::lookat() {

    return description;
}
