/*
Student: James Brooks
Class: Game Architecture

File: Corpse.cpp

Class: Corpse

Description: A special item that can hold multiple items within.
*/


#include "GameObjectMaker.h"
#include "Corpse.h"


Corpse::Corpse()
    : Item(CORPSE_ID, "Corpse") {

    setDescription("The body of my former self. The path I took was clearly incorrect. I should gather my belongings.");
    setInZoneMsg("A corpse lies on the floor where I was defeated.");
}

Corpse::~Corpse() {

}

// Add item id to corpse to be remembered
void Corpse::addItemID(int id) {

    inventory.push_back(id);
}

// Return first item in inventory of corpse, or NULL if none left
Item *Corpse::getNextItem() {

    std::list<int>::iterator iter = inventory.begin();

    if (iter != inventory.end()) {

        Item *item = GameObjectMaker::Instance().newItem(*iter);

        inventory.erase(iter);

        return item;
    }

    return NULL;
}
