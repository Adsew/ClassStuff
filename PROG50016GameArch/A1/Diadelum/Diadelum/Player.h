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

#include "Object.h"
#include "IRenderable.h"


class Item;


class Player : public Object, public IRenderable {

private:

    /***** Variables *****/

    std::map<std::string, Item *> *inventory;

    Item *weapon;

    int health;

protected:

    /***** Functions *****/

    // Return what to render to screen
    std::string render();

public:

    Player();

    virtual ~Player();

    // Initialize input manager to a usable state
    void intialize();

    // Cycle update for player
    void update();

    // If item is good, add it to player's inventory
    bool addItemToInventory(Item *item);

    // Check if player has item, if yes, return it (doesn't remove)
    Item *hasItem(std::string &name);

    // Deal damage to the player
    void takeDamage(int dmg);

    // Get current damage value from player based on current weapon
    int dealDamage();

    // Restore player to max health and remove inventory as corpse
    void restoreFromDeath();

    // Set health to a positive number
    void setHealth(int hp);

    // Return true if player hp < 0
    bool isDead();
};

#endif
