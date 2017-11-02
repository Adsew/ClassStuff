/*
Student: James Brooks
Class: Game Architecture

File: Player.cpp

Class: Player

Description: Holds all the information related to the
player at any given time.
*/


#include "Player.h"


Player::Player() {


}


Player::~Player() {


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

std::string Player::render() {

    return "I'm a player!";
}
