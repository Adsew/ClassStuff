/*
Student: James Brooks
Class: Game Architecture

File: GameEngine.cpp

Class: GameEngine

Description: main game engine runs everything else
*/


#include <iostream>
#include <ctime>

#include "GameEngine.h"
#include "tinyxml2.h"

using namespace tinyxml2;


GameEngine::GameEngine() {


}

GameEngine::~GameEngine() {


}

// Initialize the game engine to be available for start
void GameEngine::initialize(std::string &settingsFile) {

    XMLDocument docSettings;
    XMLDocument docLevel;
    
    std::string levelFileStr = "";

    docSettings.LoadFile(settingsFile.c_str());

    if (docSettings.Error() == false) {

        XMLNode *settings = docSettings.FirstChildElement("GameSettings");

        if (settings != NULL) {

            // Get game engine settings
            XMLElement *gameEngiSettings = settings->FirstChildElement("GameEngine");
            
            if (gameEngiSettings != NULL) {

                XMLElement *levelDefaultNode = gameEngiSettings->FirstChildElement("DefaultFile");

                if (levelDefaultNode != NULL) {

                    levelFileStr = levelDefaultNode->GetText();
                }
            }
            
            // Get game renderer settings
            XMLElement *rendererSettings = settings->FirstChildElement("RenderSystem");

            if (rendererSettings != NULL) {

                std::string sysName = "";
                int width = 0, height = 0;
                bool fullscreenMode = true;

                XMLElement *curElement = rendererSettings->FirstChildElement("Name");

                if (curElement != NULL) {

                    sysName = curElement->GetText();
                }

                curElement = rendererSettings->FirstChildElement("WindowSize");

                if (curElement != NULL) {

                    fullscreenMode = curElement->BoolAttribute("fullscreen");
                    width = curElement->IntAttribute("width");
                    height = curElement->IntAttribute("height");
                }

                rendSys.initialize(sysName, width, height, fullscreenMode);
            }
        }
    }
    else {

        std::cerr << "Could not open file: " << settingsFile;
    }

    docLevel.LoadFile(levelFileStr.c_str());

    if (docLevel.Error() == false) {

        XMLNode *managerNode = docLevel.FirstChildElement("GameObjectManager");

        if (managerNode != NULL) {

            XMLElement *gameObjs = managerNode->FirstChildElement("GameObjects");

            if (gameObjs != NULL) {

                // Loop and load all game objects into manager
                for (XMLElement *go = gameObjs->FirstChildElement("GameObject");
                    go != NULL;
                    go = go->NextSiblingElement("GameObject")) {

                    GameObject *newGameObj = NULL;
                    std::string name = "";

                    XMLElement *goElem = go->FirstChildElement("name");

                    if (goElem != NULL) {

                        name = goElem->GetText();
                    }

                    newGameObj = new GameObject(name);

                    goElem = go->FirstChildElement("Components");

                    // Load all components for this game object
                    for (XMLElement *comp = goElem->FirstChildElement("Component");
                        comp != NULL;
                        comp = comp->NextSiblingElement("Component")) {

                        Component *newCompObj = NULL;
                        int id = 0;

                        XMLElement *idElem = comp->FirstChildElement("id");

                        if (idElem != NULL) {

                            id = atoi(idElem->GetText());
                        }

                        newCompObj = new Component(id);

                        newGameObj->addComponent(newCompObj);
                    }

                    goMgr.addGameObject(newGameObj);
                }
            }
        }
    }
    else {

        std::cerr << "Could not open file: " << levelFileStr;
    }
}

// main game loop for running through updates
void GameEngine::gameLoop() {

    clock_t startT = clock();
    double timeElapsed = 0;
    double runTime = 10;    // Seconds
    bool isRunning = true;
    
    std::cout << "Game loop started. Running for " << runTime << " seconds...\n";

    while (isRunning) {

        rendSys.update();
        fileSys.update();
        inSys.update();
        assetMgr.update();
        goMgr.update();

        timeElapsed = (clock() - startT) / CLOCKS_PER_SEC;

        if (timeElapsed >= runTime) {

            isRunning = false;
        }
    }
}

// Display everything to the renderer
void GameEngine::display() {

    fileSys.display();
    inSys.display();
    assetMgr.display();
    goMgr.display();
    rendSys.display();
}
