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

private:

    int dropsID;    // As opposed to createsID, occurs when monster is killed, not used
    int damage;
    int health;

public:

    Monster(int idNum, std::string n);

    virtual ~Monster();

        // Interactivity functions

    std::string attack(Player *p);

    int dropItem();

    void setDropsID(int id);

    void setDamage(int dmg);

    void setHealth(int hp);
};

#endif
