#ifndef GAME_OBJECT_MAKER_H
#define GAME_OBJECT_MAKER_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObjectMaker.h

Class: GameObjectMaker

Description: A singleton class that produces the desired game object 
    with the helpf of the file system for loading the information.
*/


#include "Interactable.h"
#include "Item.h"
#include "Monster.h"


class GameObjectMaker {

private:

    GameObjectMaker();

    GameObjectMaker(GameObjectMaker &gom);

    ~GameObjectMaker();

    GameObjectMaker &operator=(GameObjectMaker &gom);

public:

    inline static GameObjectMaker &Instance() {

        static GameObjectMaker instance;

        return instance;
    }

    Item *newItem(int id);

    Interactable *newInteractable(int id);

    Monster *newMonster(int id);
};

#endif
