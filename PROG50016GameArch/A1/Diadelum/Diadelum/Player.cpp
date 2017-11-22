/*
Student: James Brooks
Class: Game Architecture

File: Player.cpp

Class: Player

Description: Holds all the information related to the
player at any given time.
*/


#include "Corpse.h"
#include "Item.h"
#include "Player.h"


#define PLAYER_MAX_HEALTH 10


Player::Player() {

    weapon = NULL;

    health = PLAYER_MAX_HEALTH;
}


Player::~Player() {

    for (std::map<std::string, Item *>::iterator iter = inventory.begin();
        iter != inventory.end();
        iter++) {

        delete iter->second;
        iter->second = NULL;
    }
}

// Initialize input manager to a usable state
void Player::intialize() {

    
}

// Cycle update for player
void Player::update() {

    std::map<std::string, Item *>::iterator iter = inventory.begin();

    while (iter != inventory.end()) {

        if (iter->second->getNeedsDeletion()) {

            delete iter->second;
            iter->second = NULL;
            iter = inventory.erase(iter);
        }
        else {

            iter++;
        }
    }
}

// Return what to render to screen
std::string Player::render() {

    std::string renderText = "HP: " + std::to_string(health) + " Weapon:";
    std::map<std::string, Item *>::iterator iter;

    if (weapon == NULL) {

        renderText += " none";
    }
    else {

        renderText += " " + weapon->getName();
    }

    renderText += " Inventory:";

    for (iter = inventory.begin(); iter != inventory.end(); iter++) {

        renderText += " " + iter->second->getName();
    }

    return renderText;
}

// If item is good, add it to player's inventory
bool Player::addItemToInventory(Item *item) {

    if (item != NULL) {

        // Special case of picking up a corpse, need to collect all items on it
        if (item->getID() == CORPSE_ID) {

            Corpse *corpse = (Corpse *)item;    // Reinterpret corpse for inventory
            Item *itemRetrieved = corpse->getNextItem();
            
            while (itemRetrieved != NULL) {

                inventory[itemRetrieved->getName()] = itemRetrieved;

                itemRetrieved = corpse->getNextItem();
            }

            delete corpse;  // No longer needed, items are taken
        }

        // Else regular item pickup
        else {

            inventory[item->getName()] = item;

            // Set new weapon if better than current
            if (item->getDamage() > 0) {

                // Note, reference is held twice, hence weapon is not explicitly deleted
                if (weapon == NULL) {

                    weapon = item;
                }
                else {

                    if (item->getDamage() > weapon->getDamage()) {

                        weapon = item;
                    }
                }
            }
        }
        
        return true;
    }

    return false;
}

// Check if player has item, if yes, return it (doesn't remove)
Item *Player::hasItem(std::string &name) {

    try {

        return inventory.at(name);
    }
    catch (const std::out_of_range &ex) {}

    return NULL;
}

// Deal damage to the player
void Player::takeDamage(int dmg) {

    health = health - dmg;

    if (health < 0) {

        health = 0;
    }
}

// Get current damage value from player based on current weapon
int Player::dealDamage() {

    if (weapon != NULL) {

        return weapon->getDamage();
    }

    return 0;
}

// Restore player to max health and remove inventory as corpse
Corpse *Player::restoreFromDeath() {

    Corpse *corpse = NULL;

    health = PLAYER_MAX_HEALTH;

    weapon = NULL;

    if (inventory.size() > 0) {

        corpse = new Corpse();

        for (std::map<std::string, Item *>::iterator iter = inventory.begin();
            iter != inventory.end();
            iter++) {

            corpse->addItemID(iter->second->getID());

            delete iter->second;
            iter->second = NULL;
        }

        inventory.clear();
    }
    
    return corpse;
}

// Set health to a positive number
void Player::setHealth(int hp) {

    if (hp > 0) {

        health = hp;
    }
}

// Return true if player hp < 0
bool Player::isDead() {

    if (health <= 0) {

        return true;
    }

    return false;
}
