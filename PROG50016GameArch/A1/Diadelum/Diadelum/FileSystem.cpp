/*
Student: James Brooks
Class: Game Architecture

File: FileSystem.cpp

Class: FileSystem

Description: Manages the input and output of files used by the game
*/


#include <string>

#include "tinyxml2.h"
#include "FileSystem.h"


using namespace tinyxml2;


FileSystem::FileSystem() {}

FileSystem::FileSystem(FileSystem &fs) {}

FileSystem::~FileSystem() {}

FileSystem &FileSystem::operator=(FileSystem &fs) { return fs; }

// Initialize the file system to a usable state
void FileSystem::initialize(std::string &settingsFile) {

    //XMLDocument docSettings;
    //XMLDocument docLevel;
    //
    //std::string levelFileStr = "";

    //docSettings.LoadFile(settingsFile.c_str());

    //if (docSettings.Error() == false) {

    //    XMLNode *settings = docSettings.FirstChildElement("GameSettings");

    //    if (settings != NULL) {

    //        // Get game engine settings
    //        XMLElement *gameEngiSettings = settings->FirstChildElement("GameEngine");
    //        
    //        if (gameEngiSettings != NULL) {

    //            XMLElement *levelDefaultNode = gameEngiSettings->FirstChildElement("DefaultFile");

    //            if (levelDefaultNode != NULL) {

    //                levelFileStr = levelDefaultNode->GetText();
    //            }
    //        }
    //        
    //        // Get game renderer settings
    //        XMLElement *rendererSettings = settings->FirstChildElement("RenderSystem");

    //        if (rendererSettings != NULL) {

    //            std::string sysName = "";
    //            int width = 0, height = 0;
    //            bool fullscreenMode = true;

    //            XMLElement *curElement = rendererSettings->FirstChildElement("Name");

    //            if (curElement != NULL) {

    //                sysName = curElement->GetText();
    //            }

    //            curElement = rendererSettings->FirstChildElement("WindowSize");

    //            if (curElement != NULL) {

    //                fullscreenMode = curElement->BoolAttribute("fullscreen");
    //                width = curElement->IntAttribute("width");
    //                height = curElement->IntAttribute("height");
    //            }

    //            rendSys.initialize(sysName, width, height, fullscreenMode);
    //        }
    //    }
    //}
    //else {

    //    std::cerr << "Could not open file: " << settingsFile;
    //}

    //docLevel.LoadFile(levelFileStr.c_str());

    //if (docLevel.Error() == false) {

    //    XMLNode *managerNode = docLevel.FirstChildElement("GameObjectManager");

    //    if (managerNode != NULL) {

    //        XMLElement *gameObjs = managerNode->FirstChildElement("GameObjects");

    //        if (gameObjs != NULL) {

    //            // Loop and load all game objects into manager
    //            for (XMLElement *go = gameObjs->FirstChildElement("GameObject");
    //                go != NULL;
    //                go = go->NextSiblingElement("GameObject")) {

    //                GameObject *newGameObj = NULL;
    //                std::string name = "";

    //                XMLElement *goElem = go->FirstChildElement("name");

    //                if (goElem != NULL) {

    //                    name = goElem->GetText();
    //                }

    //                newGameObj = new GameObject(name);

    //                goElem = go->FirstChildElement("Components");

    //                // Load all components for this game object
    //                for (XMLElement *comp = goElem->FirstChildElement("Component");
    //                    comp != NULL;
    //                    comp = comp->NextSiblingElement("Component")) {

    //                    Component *newCompObj = NULL;
    //                    int id = 0;

    //                    XMLElement *idElem = comp->FirstChildElement("id");

    //                    if (idElem != NULL) {

    //                        id = atoi(idElem->GetText());
    //                    }

    //                    newCompObj = new Component(id);

    //                    newGameObj->addComponent(newCompObj);
    //                }

    //                goMgr.addGameObject(newGameObj);
    //            }
    //        }
    //    }
    //}
    //else {

    //    std::cerr << "Could not open file: " << levelFileStr;
    //}
}

// Cycle update for file system
void FileSystem::update() {


}

// Display relavent information from the file system to the screen
void FileSystem::display() {


}
