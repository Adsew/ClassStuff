/*
Student: James Brooks
Class: Game Architecture

File: SceneManager.cpp

Class: SceneManager

Description: Acts and the data controller between the active game scene
and the input. It will contain what data is currently active in the
game world.
*/


#include "Player.h"
#include "Zone.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "SceneManager.h"


SceneManager::SceneManager()
    : actions(9) {

    actions[0] = &SceneManager::noAction;
    actions[1] = &SceneManager::move;
    actions[2] = &SceneManager::use;
    actions[3] = &SceneManager::search;
    actions[4] = &SceneManager::attack;
    actions[5] = &SceneManager::help;
    actions[6] = &SceneManager::save;
    actions[7] = &SceneManager::exit;
    actions[8] = &SceneManager::noAction;   // For starting with "with", a connector keyword

    exitFlag = false;
}

SceneManager::~SceneManager() {

    delete player;
    delete activeZone;
}

// Initialize input manager to a usable state
void SceneManager::intialize() {

    player = new Player();
    activeZone = new Zone("test", player);

    RenderSystem::Instance().addIRenderable(activeZone);
}

// Cycle update for input manager
bool SceneManager::update() {

    std::list<std::pair<int, std::string>> action = InputSystem::Instance().getInput();

    if (action.size() > 0) {

        (this->*actions[(*action.begin()).first])(action);
    }

    if (exitFlag == true) {

        return false;   // Set isRunning false in engine
    }

    return true;
}


    // Action functions based on input


void SceneManager::noAction(std::list<std::pair<int, std::string>> &action) {

    activeZone->noAction(action);
}

void SceneManager::move(std::list<std::pair<int, std::string>> &action) {

    activeZone->move(action);

    if (activeZone->movingFlagStatus() == true) {

        // get zone to move to and load from file and swap
    }
}

void SceneManager::use(std::list<std::pair<int, std::string>> &action) {

    activeZone->use(action);
}

void SceneManager::search(std::list<std::pair<int, std::string>> &action) {

    activeZone->search(action);
}

void SceneManager::attack(std::list<std::pair<int, std::string>> &action) {

    activeZone->attack(action);
}

void SceneManager::help(std::list<std::pair<int, std::string>> &action) {

    activeZone->help();
}

void SceneManager::save(std::list<std::pair<int, std::string>> &action) {


}

void SceneManager::exit(std::list<std::pair<int, std::string>> &action) {

    exitFlag = true;
}
