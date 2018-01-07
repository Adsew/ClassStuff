#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObjectManager.h

Class: GameObjectManager

Description: Maintains the memory and functionality of all game objects currently loaded.
*/


#include "ISystem.h"


class GameObject;


class GameObjectManager : public ISystem {

    friend class GameEngine;

    
    /***** Variables *****/

private:
	
    std::list<GameObject *> gameObjects;        // Currently updating
    std::list<GameObject *> recentlyCreated;    // To be added to list next cycle

    /***** Functions *****/

private:

    GameObjectManager() = default;

    ~GameObjectManager();

    GameObjectManager(const GameObjectManager &gom) = default;

protected:

	virtual void initialize() override;
	
    virtual void clean() override;

    virtual void update() override;

public:

    inline static GameObjectManager &Instance() {

        static GameObjectManager instance;

        return instance;
    }

    GameObject *createGameObject();
};

#endif // !GAME_OBJECT_MANAGER_H
