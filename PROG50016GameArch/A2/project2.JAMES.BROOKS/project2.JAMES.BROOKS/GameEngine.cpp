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


void GameEngine::initialize(const char *settingsFile) {

    Timer::Instance().initialize();
	AssetManager::Instance().initialize();
	InputManager::Instance().initialize();
	RenderSystem::Instance().initialize();
	GameObjectManager::Instance().initialize();

	// Needs to be at the end because we will load a default file
	FileSystem::Instance().initialize(settingsFile);
}

void GameEngine::gameLoop() {

    bool running = true;

    Timer::Instance().beginTiming();

	while (running) {

		InputManager::Instance().update();

		AssetManager::Instance().update();

		GameObjectManager::Instance().update();

		RenderSystem::Instance().update();

        Timer::Instance().update();

		std::cout << "Current Game Time: " << Timer::Instance().runTime << " Delta Time: " << Timer::Instance().deltaTime << std::endl;
	}
}
