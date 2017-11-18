/*
Student: James Brooks
Class: Game Architecture

File: Player.cpp

Class: Player

Description: Holds all the information related to the
player at any given time.
*/


#include "Item.h"
#include "Player.h"


Player::Player() {

    inventory = new std::map<std::string, Item *>();

    health = 10;    // 10 health default
}


Player::~Player() {

    for (std::map<std::string, Item *>::iterator iter = inventory->begin();
        iter != inventory->end();
        iter++) {

        delete iter->second;
        iter->second = NULL;
    }

    delete inventory;
}

// Initialize input manager to a usable state
void Player::intialize() {

    
}

// Cycle update for player
void Player::update() {

    std::map<std::string, Item *>::iterator iter = inventory->begin();

    while (iter != inventory->end()) {

        if (iter->second->getNeedsDeletion()) {

            delete iter->second;
            iter->second = NULL;
            iter = inventory->erase(iter);
        }
        else {

            iter++;
        }
    }
}

// Return what to render to screen
std::string Player::render() {

    std::string renderText = "HP: " + std::to_string(health) + "Inventory:";
    std::map<std::string, Item *>::iterator iter;

    for (iter = inventory->begin(); iter != inventory->end(); iter++) {

        renderText += " " + iter->second->getName();
    }

    return renderText;
}

// If item is good, add it to player's inventory
bool Player::addItemToInventory(Item *item) {

    if (item != NULL) {

        (*inventory)[item->getName()] = item;

        return true;
    }

    return false;
}

// Check if player has item, if yes, return it (doesn't remove)
Item *Player::hasItem(std::string &name) {

    try {

        return inventory->at(name);
    }
    catch (const std::out_of_range &ex) {}

    return NULL;
}

// Set health to a positive number
void Player::setHealth(int hp) {

    if (hp > 0) {

        health = hp;
    }
}
