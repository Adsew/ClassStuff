#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

/*
Student: James Brooks
Class: Game Architecture

File: GameEngine.h

Class: GameEngine

Description: main game engine runs everything else
*/


#include <string>

#include "SceneManager.h"


class GameEngine {

private:

    /***** Variables *****/

    SceneManager scene;

    bool isRunning;

public:

    /***** Functions *****/

    GameEngine();

    ~GameEngine();

    // Initialize the game engine to be available for start
    bool initialize(std::string &settingsFile);

    // main game loop for running through updates
    void gameLoop();
};

#endif
