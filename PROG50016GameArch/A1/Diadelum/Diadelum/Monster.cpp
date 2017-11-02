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
}

Monster::~Monster() {


}

std::string Monster::attack(Player *p) {

    return "I ATTACK YOU RAWR!";
}
