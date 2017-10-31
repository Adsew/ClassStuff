/*
Student: James Brooks
Class: Game Architecture

File: GameEngine.cpp

Class: GameEngine

Description: main game engine runs everything else
*/


#include "GameEngine.h"


GameEngine::GameEngine() {

}

GameEngine::~GameEngine() {


}

// Initialize the game engine to be available for start
void GameEngine::initialize(std::string &settingsFile) {

    
}

// main game loop for running through updates
void GameEngine::gameLoop() {

    bool isRunning = true;
    
    while (isRunning) {

        inSys.update();

        RenderSystem::Instance().update();
    }
}

// Display everything to the renderer
void GameEngine::display() {

}
