#ifndef CORPSE_H
#define CORPSE_H

/*
Student: James Brooks
Class: Game Architecture

File: Corpse.h

Class: Corpse

Description: A special item that can hold multiple items within.
*/


#include <list>
#include "Item.h"


#define CORPSE_ID 5000


class Corpse : public Item {

private:

    std::list<int> inventory;

public:

    Corpse();

    virtual ~Corpse();

    // Add item id to corpse to be remembered
    void addItemID(int id);

    // Return first item in inventory of corpse, or NULL if none left
    Item *getNextItem();

    // Return first item in inventory of corpse as an ID, or NULL if none left
    int getNextItemID();
};

#endif
