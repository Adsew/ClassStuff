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
#include "GameObjectMaker.h"
#include "SceneManager.h"


SceneManager::SceneManager()
    : actions(10) {

    actions[0] = &SceneManager::noAction;
    actions[1] = &SceneManager::move;
    actions[2] = &SceneManager::use;
    actions[3] = &SceneManager::search;
    actions[4] = &SceneManager::pickup;
    actions[5] = &SceneManager::attack;
    actions[6] = &SceneManager::help;
    actions[7] = &SceneManager::save;
    actions[8] = &SceneManager::exit;
    actions[9] = &SceneManager::noAction;   // For starting with a connector keyword

    exitFlag = false;
}

SceneManager::~SceneManager() {

    delete player;
    delete activeZone;
}

// Initialize input manager to a usable state
void SceneManager::intialize() {

    player = new Player();
    activeZone = GameObjectMaker::Instance().newZone("meeting quarter");
    
    if (activeZone != NULL) {

        activeZone->setPlayer(player);

        RenderSystem::Instance().addIRenderable(activeZone);
    }
    else {

        exitFlag = true;
    }
}

// Cycle update for input manager
bool SceneManager::update() {

    std::list<std::pair<int, std::string>> action = InputSystem::Instance().getInput();

    if (action.size() > 0 && player != NULL && activeZone != NULL) {

        (this->*actions[(*action.begin()).first])(action);

        player->update();
        activeZone->update();
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

        Zone *tempZone = GameObjectMaker::Instance().newZone(activeZone->getZoneToMoveTo());

        if (tempZone != NULL) {

            RenderSystem::Instance().removeIRenderable(activeZone);

            delete activeZone;

            activeZone = tempZone;
            activeZone->setPlayer(player);

            RenderSystem::Instance().addIRenderable(activeZone);
        }
    }
}

void SceneManager::use(std::list<std::pair<int, std::string>> &action) {

    activeZone->use(action);
}

void SceneManager::search(std::list<std::pair<int, std::string>> &action) {

    activeZone->search(action);
}

void SceneManager::pickup(std::list<std::pair<int, std::string>> &action) {

    activeZone->pickup(action);
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
