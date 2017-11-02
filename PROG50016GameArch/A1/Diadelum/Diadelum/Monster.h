#ifndef MONSTER_H
#define MONSTER_H

/*
Student: James Brooks
Class: Game Architecture

File: Monster.h

Class: Monster

Description: An enemy that can be attacked or attack the player.
*/


#include "Interactable.h"


class Player;


class Monster : public Interactable {

public:

    Monster(int idNum, std::string n);

    virtual ~Monster();

        // Interactivity functions

    std::string attack(Player *p);
};

#endif
