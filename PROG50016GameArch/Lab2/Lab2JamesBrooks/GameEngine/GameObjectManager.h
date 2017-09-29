#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObjectManager.h

Class: GameObjectManager

Description: Manages list of game objects in a given scene
*/


#include <list>

#include "GameObject.h"


class GameObjectManager {

private:

    /***** Variables *****/

    std::list<GameObject *> gameObjects;


public:

    /***** Functions *****/

    GameObjectManager();

    ~GameObjectManager();

    // Add game object to the manager
    void addGameObject(GameObject *go);

    // Remove game object from the manager
    void removeGameObject(GameObject *go);

    // Initialize manager to usable status
    void initialize();

    // Cycle update from manager
    void update();

    // Display game objects to the screen
    void display();
};


#endif
