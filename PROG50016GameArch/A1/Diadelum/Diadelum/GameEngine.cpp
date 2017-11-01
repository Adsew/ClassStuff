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


GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

// Initialize the game engine to be available for start
void GameEngine::initialize(std::string &settingsFile) {

    InputSystem::Instance().initialize();
    RenderSystem::Instance().initialize();
    scene.intialize();
}

// main game loop for running through updates
void GameEngine::gameLoop() {

    bool isRunning = true;
    
    while (isRunning) {

        InputSystem::Instance().update();

        isRunning = scene.update();

        RenderSystem::Instance().update();
    }
}
