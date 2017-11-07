/*
Student: James Brooks
Class: Game Architecture

File: GameEngine.cpp

Class: GameEngine

Description: main game engine runs everything else
*/


#include "FileSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "GameEngine.h"


GameEngine::GameEngine() {

    isRunning = false;
}

GameEngine::~GameEngine() {}

// Initialize the game engine to be available for start
bool GameEngine::initialize(std::string &settingsFile) {

    FileSystem::Instance().initialize("game/assets", "game/map");
    InputSystem::Instance().initialize();
    RenderSystem::Instance().initialize();
    scene.intialize();

    isRunning = true;

    return isRunning;
}

// main game loop for running through updates
void GameEngine::gameLoop() {

    while (isRunning) {

        InputSystem::Instance().update();

        isRunning = scene.update();

        RenderSystem::Instance().update();
    }
}
