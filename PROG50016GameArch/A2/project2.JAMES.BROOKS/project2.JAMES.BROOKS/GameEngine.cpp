/*
Student: James Brooks
Class: Game Architecture

File: GameEngine.cpp

Class: GameEngine

Description: Holds the game loop and runs the major systems that run the game.
*/


#include "Core.h"

#include "AssetManager.h"
#include "FileSystem.h"
#include "InputManager.h"
#include "RenderSystem.h"
#include "GameObjectManager.h"
#include "GameEngine.h"


void GameEngine::initialize() {

	AssetManager::Instance().initialize();
	InputManager::Instance().initialize();
	RenderSystem::Instance().initialize();
	GameObjectManager::Instance().initialize();

	// Needs to be at the end because we will load a default file
	FileSystem::Instance().initialize();
}

void GameEngine::gameLoop() {

	float gameTime = 0.0f;
	clock_t _time;
	float deltaTime = 0.0f;

	while (true) {
		_time = clock();

		InputManager::Instance().update(deltaTime);

		FileSystem::Instance().update(deltaTime);

		AssetManager::Instance().update(deltaTime);

		GameObjectManager::Instance().update(deltaTime);

		RenderSystem::Instance().update(deltaTime);

		_time = clock() - _time;
		deltaTime = ((float)_time) / ((clock_t)1000);
		gameTime += deltaTime;

		std::cout << "Current Game Time: " << gameTime << " Delta Time: " << deltaTime << std::endl;
	}
}
