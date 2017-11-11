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
#include "Zone.h"
#include "GameObjectMaker.h"


GameObjectMaker::GameObjectMaker() {}

GameObjectMaker::GameObjectMaker(GameObjectMaker &gom) {}

GameObjectMaker::~GameObjectMaker() {}

GameObjectMaker &GameObjectMaker::operator=(GameObjectMaker &gom) { return gom; }

Item *GameObjectMaker::newItem(int id) {

    Item *item = NULL;

    FileSystem::Instance().useFile("items");
    FileSystem::Instance().traverseToElement("items");
    FileSystem::Instance().traverseToElement("I" + id);

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

Zone *GameObjectMaker::newZone(const char *name) {


}

Zone *GameObjectMaker::newZone(std::string &name) {

    return this->newZone(name.c_str());
}
