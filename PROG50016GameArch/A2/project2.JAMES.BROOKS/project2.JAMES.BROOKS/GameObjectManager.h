#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObjectManager.h

Class: GameObjectManager

Description: Maintains the memory and funcitonality of all game objects currently loaded.
*/


#include "ISystem.h"


class GameObject;


class GameObjectManager : public ISystem {

friend class GameEngine;

    
    /***** Variables *****/

private:
	
    std::list<GameObject*> gameObjects;


    /***** Functions *****/

private:

    GameObjectManager() = default;

    ~GameObjectManager() = default;

    GameObjectManager(const GameObjectManager& other) = default;

protected:

	void initialize() override;
	
    void update() override;

public:

    inline static GameObjectManager& Instance() {

        static GameObjectManager instance;

        return instance;
    }
};

#endif // !GAME_OBJECT_MANAGER_H
