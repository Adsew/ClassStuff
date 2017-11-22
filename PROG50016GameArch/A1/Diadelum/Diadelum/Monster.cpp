/*
Student: James Brooks
Class: Game Architecture

File: Monster.cpp

Class: Monster

Description: An enemy that can be attacked or attack the player.
*/


#include "Player.h"
#include "Monster.h"


Monster::Monster(int idNum, std::string n)
    : Interactable(idNum, n) {

    numUses = -1;
    dropsID = 0;
    damage = 1;
    health = 1;
}

Monster::~Monster() {


}

std::string Monster::attack(Player *p) {

    int pDmg = p->dealDamage();
    std::string msg = "You dealt " + std::to_string(pDmg) + " to " + name + ".";

    health = health - pDmg;

    // Can't retaliate if dead
    if (health > 0) {

        p->takeDamage(damage);

        msg += " The " + name + " dealt " + std::to_string(damage) + " to you.";
    }
    else {

        msg += " You kill the " + name + ".";

        inUse = true;   // Allow drops and unlocks to be performed since dead

        destroy();
    }

    return msg;
}

std::string Monster::getAttackedBy(Player *p) {

    return "";
}

void Monster::setDropsID(int id) {

    dropsID = id;
}

void Monster::setDamage(int dmg) {

    if (dmg < 0) {
    
        damage = 0;
    }
    else {

        damage = dmg;
    }
}

void Monster::setHealth(int hp) {

    if (hp < 0) {

        health = 0;
    }
    else {

        health = hp;
    }
}
