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
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "GameEngine.h"


void GameEngine::initialize(const char *settingsFile) {

    Timer::Instance().initialize();
	AssetManager::Instance().initialize();
	InputManager::Instance().initialize();
	RenderSystem::Instance().initialize();
    SceneManager::Instance().initialize();
    ComponentManager::Instance().initialize();
	GameObjectManager::Instance().initialize();
    
	// Needs to be at the end because we will load a default file
	FileSystem::Instance().initialize(settingsFile);
}

void GameEngine::gameLoop() {

    Timer::Instance().beginTiming();

	while (!InputManager::Instance().gameCloseTriggered) {

		InputManager::Instance().update();

		AssetManager::Instance().update();

		GameObjectManager::Instance().update();

        ComponentManager::Instance().update();

		RenderSystem::Instance().update();

        SceneManager::Instance().update();

        Timer::Instance().update();

		//DEBUG_LOG("Current Game Time: " << Timer::Instance().runTime << " Delta Time: " << Timer::Instance().deltaTime);
	}
}
