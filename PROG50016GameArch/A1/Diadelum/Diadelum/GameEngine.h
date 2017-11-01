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
#include "GameObjectManager.h"


class GameEngine {

private:

    /***** Variables *****/

    //GameObjectManager goMgr;
    SceneManager scene;

public:

    /***** Functions *****/

    GameEngine();

    ~GameEngine();

    // Initialize the game engine to be available for start
    void initialize(std::string &settingsFile);

    // main game loop for running through updates
    void gameLoop();
};

#endif
