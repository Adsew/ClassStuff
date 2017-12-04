#pragma once

class ISystem;

class GameEngine
{

public:
	inline static GameEngine& Instance()
	{
		static GameEngine instance;
		return instance;
	}

	void initialize();
	void gameLoop();

private:
	GameEngine() = default;
	~GameEngine() = default;
	GameEngine(const GameEngine& other) = default;
};

