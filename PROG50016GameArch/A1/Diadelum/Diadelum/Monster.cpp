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

    return "I ATTACK YOU RAWR!";
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
