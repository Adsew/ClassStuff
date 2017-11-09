/*
Student: James Brooks
Class: Game Architecture

File: GameObjectMaker.cpp

Class: GameObjectMaker

Description: A singleton class that produces the desired game object
with the helpf of the file system for loading the information.
*/


#include "FileSystem.h"
#include "Interactable.h"
#include "Item.h"
#include "Monster.h"
#include "GameObjectMaker.h"


GameObjectMaker::GameObjectMaker() {}

GameObjectMaker::GameObjectMaker(GameObjectMaker &gom) {}

GameObjectMaker::~GameObjectMaker() {}

GameObjectMaker &GameObjectMaker::operator=(GameObjectMaker &gom) { return gom; }

Item *GameObjectMaker::newItem(int id) {

    Item *item = NULL;

    item = new Item(id, "");

    return item;
}

Interactable *GameObjectMaker::newInteractable(int id) {

    Interactable *inter = NULL;

    inter = new Interactable(id, "");

    return inter;
}

Monster *GameObjectMaker::newMonster(int id) {

    Monster *mon = NULL;

    mon = new Monster(id, "");

    return mon;
}
