/*
Student: James Brooks
Class: Game Architecture

File: GameObjectMaker.cpp

Class: GameObjectMaker

Description: A singleton class that produces the desired game object
with the helpf of the file system for loading the information.
*/


#include "GameObjectMaker.h"


GameObjectMaker::GameObjectMaker() {}

GameObjectMaker::GameObjectMaker(GameObjectMaker &gom) {}

GameObjectMaker::~GameObjectMaker() {}

GameObjectMaker &GameObjectMaker::operator=(GameObjectMaker &gom) { return gom; }

Item *GameObjectMaker::newItem(int id) {

    Item *item = NULL;

    //FileSystem::Instance().(load details)(id);
    item = new Item(id, "");

    return item;
}

Interactable *GameObjectMaker::newInteractable(int id) {

    Interactable *inter = NULL;

    //FileSystem::Instance().(load details)(id);
    inter = new Interactable(id, "");

    return inter;
}

Monster *GameObjectMaker::newMonster(int id) {

    Monster *mon = NULL;

    //FileSystem::Instance().(load details)(id);
    mon = new Monster(id, "");

    return mon;
}
