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

#include "RenderSystem.h"
#include "FileSystem.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameObjectManager.h"


class GameEngine {

private:

    /***** Variables *****/

    RenderSystem rendSys;
    FileSystem fileSys;
    InputManager inSys;
    AssetManager assetMgr;
    GameObjectManager goMgr;


public:

    /***** Functions *****/

    GameEngine();

    ~GameEngine();

    // Initialize the game engine to be available for start
    void initialize(std::string &settingsFile);

    // main game loop for running through updates
    void gameLoop();

    // Display everything to the renderer
    void display();
};

#endif
