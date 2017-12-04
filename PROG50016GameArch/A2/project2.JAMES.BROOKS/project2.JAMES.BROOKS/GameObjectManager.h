#pragma once

#include <list>
#include "ISystem.h"

class GameObject;

class GameObjectManager : public ISystem
{
private:
	std::list<GameObject*> gameObjects;

public:
	inline static GameObjectManager& Instance()
	{
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

	friend class GameEngine;
};

