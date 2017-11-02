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

    // Items always used on something else to produce effect if not another item
    go->useWith(this);

    if (inUse) {

        return onUseMsg;
    }
    
    return "The " + name + " does not work with the " + go->getName() + ".";
}

std::string Item::useWith(Item *item) {

    if (item->getID() == worksWithID) {

        inUse = true;
        item->setInUse(true);

        numUses--;
        item->setNumUses(item->getNumUses() - 1);

        // If less than 0 means unlimted uses
        if (numUses == 0) {

            needsDeletion = true;
        }
        if (item->getNumUses() == 0) {

            item->setNeedsDeletion(true);
        }

        return onUseMsg;
    }

    return "The " + name + " does not work with the " + item->getName() + ".";
}

std::string Item::lookat() {

    return description;
}

