#ifndef ITEM_H
#define ITEM_H

/*
Student: James Brooks
Class: Game Architecture

File: Item.h

Class: Item

Description: Items that can be carried by the player.
*/


#include <map>

#include "GameObject.h"


class Item : public GameObject {

private:

    int damage;

public:

    /***** Functions *****/

    Item(int idNum, std::string n);

    virtual ~Item();

        // Interactivity functions

    std::string use();

    std::string useWith(GameObject *go);

    std::string lookat();

    void setDamage(int damage);
};

#endif
