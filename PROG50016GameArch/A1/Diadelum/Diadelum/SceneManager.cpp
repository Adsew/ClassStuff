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
#include "InputCodes.h"
#include "SceneManager.h"


SceneManager::SceneManager()
    : actions(IN_CODE_COUNT) {

    actions[IN_CODE_NOTHING] = &SceneManager::noAction;
    actions[IN_CODE_MOVE] = &SceneManager::move;
    actions[IN_CODE_USE] = &SceneManager::use;
    actions[IN_CODE_SEARCH] = &SceneManager::search;
    actions[IN_CODE_PICKUP] = &SceneManager::pickup;
    actions[IN_CODE_TALK] = &SceneManager::talk;
    actions[IN_CODE_ATTACK] = &SceneManager::attack;
    actions[IN_CODE_HELP] = &SceneManager::help;
    actions[IN_CODE_SAVE] = &SceneManager::save;
    actions[IN_CODE_EXIT] = &SceneManager::exit;
    actions[IN_CODE_CONNECT] = &SceneManager::noAction;   // For starting with a connector keyword

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
    
    if (activeZone != NULL && player != NULL) {

        activeZone->setPlayer(player);
        
        RenderSystem::Instance().addIRenderable(player);
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

void SceneManager::talk(std::list<std::pair<int, std::string>> &action) {

    activeZone->talk(action);
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
