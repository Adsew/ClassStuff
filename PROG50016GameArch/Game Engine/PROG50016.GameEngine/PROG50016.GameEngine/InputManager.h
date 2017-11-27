#pragma once

#include "ISystem.h"

class InputManager : public ISystem
{

public:
	inline static InputManager& Instance()
	{
		static InputManager instance;
		return instance;
	}

protected:
	void initialize() override;
	void update(float _deltaTime) override;

private:
	InputManager() = default;
	~InputManager() = default;
	InputManager(const InputManager& other) = default;

	friend class GameEngine;
};

