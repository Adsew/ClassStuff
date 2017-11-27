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


#include <string>


class Zone;
class Item;
class Interactable;
class Monster;
class NPC;
class Player;


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

    // Create a new item given an id
    Item *newItem(int id);

    // Create a new interactable given an id
    Interactable *newInteractable(int id);

    // Create a new monster given an id
    Monster *newMonster(int id);

    // Create a new NPC given a name
    NPC *newNPC(int id);

    // Create a new zone given a name in the map
    Zone *newZone(const char *name);

    // Create a new zone given a name in the map
    Zone *newZone(std::string &name);

    // Load a zone from the current player save
    Zone *loadZone(const char *name, const char *saveName);

    // Load a zone from the current player save
    Zone *loadZone(std::string &name, std::string &saveName);
    
    // Create a new player from the base player
    Player *newPlayer(const char *name);

    // Create a new player from the base player
    Player *newPlayer(std::string &name);

    // Load a pre-existing player from save file
    Player *loadPlayer(const char *name);

    // Load a pre-existing player from save file
    Player *loadPlayer(std::string &name);
};

#endif
