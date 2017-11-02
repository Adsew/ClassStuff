#ifndef PLAYER_H
#define PLAYER_H

/*
Student: James Brooks
Class: Game Architecture

File: Player.h

Class: Player

Description: Holds all the information related to the
    player at any given time.
*/


#include <map>

#include "Item.h"
#include "Object.h"
#include "IRenderable.h"

class Player : public Object, public IRenderable {

public:

    /***** Variables *****/

    std::map<std::string, Item *> inventory;

protected:

    /***** Functions *****/

    std::string render();

public:

    Player();

    virtual ~Player();

    // Initialize input manager to a usable state
    void intialize();

    // Cycle update for player
    void update();
};

#endif
