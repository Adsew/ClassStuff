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
#include "SaveStateManager.h"
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

    player = NULL;
    activeZone = NULL;

    exitFlag = false;
}

SceneManager::~SceneManager() {

    delete player;
    delete activeZone;
}

// Initialize input manager to a usable state
void SceneManager::intialize() {

    // "Title Screen" initialization
    std::string name = "";

    while (name.length() == 0) {

        RenderSystem::Instance().directToOut("What is your name?");
        name = InputSystem::Instance().directFromInput();
    }

    player = SaveStateManager::Instance().loadPlayer(name);

    if (player != NULL) {

        activeZone = SaveStateManager::Instance().loadZone(player->getCurrentZone(), name);
        
        // Load default zone, since no modified version in save
        if (activeZone == NULL) {

            activeZone = GameObjectMaker::Instance().newZone(player->getCurrentZone());
        }
    }
    
    if (player == NULL) {

        player = GameObjectMaker::Instance().newPlayer(name);
        SaveStateManager::Instance().createTempSave(name);
    }
    // Zone not saved by player, start in starting zone (no save data)
    if (activeZone == NULL) {

        activeZone = GameObjectMaker::Instance().newZone("meeting quarter");
    }

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

    if (activeZone->movingFlagStatus() == true) {

        Zone *tempZone = SaveStateManager::Instance().loadZone(activeZone->getZoneToMoveTo(), player->getName());
        
        // If null, player has not made any changes to this zone yet, so load fresh one
        if (tempZone == NULL) {

            tempZone = GameObjectMaker::Instance().newZone(activeZone->getZoneToMoveTo());
        }
        
        if (tempZone != NULL) {

            RenderSystem::Instance().removeIRenderable(activeZone);

            if (activeZone->getModified()) {

                SaveStateManager::Instance().saveZone(player->getName(), activeZone);
            }

            delete activeZone;

            activeZone = tempZone;
            activeZone->setPlayer(player);

            RenderSystem::Instance().addIRenderable(activeZone);
        }
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

    if (activeZone->getModified()) {

        SaveStateManager::Instance().saveZone(player->getName(), activeZone);
    }

    if (SaveStateManager::Instance().saveGame(player)) {

        activeZone->setMessageToPlayer("Save successful!");
    }
    else {

        activeZone->setMessageToPlayer("Could not save game.");
    }
}

void SceneManager::exit(std::list<std::pair<int, std::string>> &action) {

    exitFlag = true;
}
