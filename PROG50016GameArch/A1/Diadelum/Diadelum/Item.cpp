/*
Student: James Brooks
Class: Game Architecture

File: Item.cpp

Class: Item

Description: Items that can be carried by the player.
*/


#include "Item.h"


Item::Item(int idNum, std::string n)
    : GameObject(idNum, n) {

    damage = 0;
}

Item::~Item() {

}

    // Interactivity functions

std::string Item::use() {

    if (worksWithID == 0) {

        inUse = true;
        numUses--;

        if (numUses == 0) {

            needsDeletion = true;
        }
        
        return onUseMsg;
    }

    return "The " + name + " has no effect by itself.";
}

std::string Item::useWith(GameObject *go) {

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

std::string Item::lookat() {

    return description;
}

void Item::setDamage(int dmg) {

    if (dmg < 0) {

        damage = 0;
    }
    else {

        damage = dmg;
    }
}
