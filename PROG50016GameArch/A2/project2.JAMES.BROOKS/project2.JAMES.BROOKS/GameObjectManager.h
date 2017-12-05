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

private:
	
    std::list<GameObject*> gameObjects;

public:
	
    inline static GameObjectManager& Instance() {

		static GameObjectManager instance;
		return instance;
	}

protected:

	void initialize() override;
	
    void update(float _deltaTime) override;

private:
	
    GameObjectManager() = default;
	
    ~GameObjectManager() = default;
	
    GameObjectManager(const GameObjectManager& other) = default;
};

#endif // !GAME_OBJECT_MANAGER_H
