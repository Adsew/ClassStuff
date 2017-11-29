/*
Student: James Brooks
Class: Game Architecture

File: SaveStateManager.cpp

Class: SaveStateManager

Description: Manages the files and data used to save and load the
persistant state of the current game world.
*/


#include "Player.h"
#include "Corpse.h"
#include "Zone.h"
#include "GameObject.h"
#include "FileSystem.h"
#include "GameObjectMaker.h"
#include "SaveStateManager.h"


class Item;
class Interactable;
class Monster;
class NPC;


SaveStateManager::SaveStateManager() {}

SaveStateManager::SaveStateManager(SaveStateManager &ssm) {}

SaveStateManager::~SaveStateManager() {}

SaveStateManager &SaveStateManager::operator=(SaveStateManager &ssm) { return ssm; }

// Create a temp save file with a given name to work with (used with new games)
void SaveStateManager::createTempSave(const char *name) {

    FileSystem::Instance().createTempFile(name);
    FileSystem::Instance().newElement("Player");
    FileSystem::Instance().traverseToParentElement();
    FileSystem::Instance().newElement("Zones");
}

// Create a temp save file with a given name to work with (used with new games)
void SaveStateManager::createTempSave(std::string &name) {

    this->createTempSave(name.c_str());
}

// Load a pre-existing player from save file
Player *SaveStateManager::loadPlayer(const char *name) {

    FileSystem *fs = &FileSystem::Instance();
    std::string nameStr = name;
    std::string fileName = "../saves/" + nameStr + ".soul";

    if (fs->loadFile(name, fileName.c_str())) {

        if (fs->useFile(name)) {

            Player *player = new Player(name);
            std::list<int> items;

            if (fs->traverseToElement("Player")) {

                std::string tempZone = "";
                int tempInt = 0;

                fs->getAttribute("health", tempInt);
                player->setHealth(tempInt);

                fs->getAttribute("zone", tempZone);
                player->setCurrentZone(tempZone);

                if (fs->traverseToElement("Inventory")) {
                    if (fs->traverseToChildElement()) {

                        do {

                            fs->getAttribute("id", tempInt);

                            items.push_back(tempInt);

                        } while (fs->traverseToSyblingElement());
                    }
                }
            }

            for (std::list<int>::iterator iter = items.begin(); iter != items.end(); iter++) {

                player->addItemToInventory(GameObjectMaker::Instance().newItem(*iter));
            }

            return player;
        }
    }

    return NULL;
}

// Load a pre-existing player from save file
Player *SaveStateManager::loadPlayer(std::string &name) {

    return this->loadPlayer(name.c_str());
}

// Load a zone from the current player save
Zone *SaveStateManager::loadZone(const char *zoneName, const char *saveName) {

    FileSystem *fs = &FileSystem::Instance();

    if (fs->useFile(saveName)) {

        GameObjectMaker *gom = &GameObjectMaker::Instance();
        Zone *zone = NULL;
        std::string tempName = zoneName;

        for (unsigned int i = 0; i < tempName.length(); i++) {

            if (tempName[i] == ' ') {

                tempName[i] = '_';
            }
        }

        zoneName = tempName.c_str();

        fs->traverseToElement("Zones");

        // Zone exists, begin to load details
        if (fs->traverseToElement(zoneName)) {

            std::list<int> items;
            std::list<int> interactables;
            std::list<int> monsters;
            std::list<int> npcs;
            std::list<int> corpse;
            std::string tempStr;
            int tempInt = 0;
            bool tempBool = true;

            zone = new Zone(zoneName);

            if (fs->traverseToElement("Description")) {

                if (fs->getElementText(tempStr)) {

                    zone->setDescription(tempStr);
                }

                fs->traverseToParentElement();
            }

            if (fs->traverseToElement("Items")) {
                if (fs->traverseToChildElement()) {

                    do {

                        if (fs->getAttribute("id", tempInt)) {

                            if (tempInt == CORPSE_ID) {

                                if (fs->traverseToChildElement()) {

                                    do {

                                        if (fs->getAttribute("id", tempInt)) {

                                            corpse.push_back(tempInt);
                                        }
                                        
                                    } while (fs->traverseToSyblingElement());

                                    fs->traverseToParentElement();
                                }
                            }
                            else {

                                items.push_back(tempInt);
                            }
                        }

                    } while (fs->traverseToSyblingElement());

                    fs->traverseToParentElement();
                }

                fs->traverseToParentElement();
            }

            if (fs->traverseToElement("Interactables")) {
                if (fs->traverseToChildElement()) {

                    do {

                        if (fs->getAttribute("id", tempInt)) {

                            interactables.push_back(tempInt);
                        }

                    } while (fs->traverseToSyblingElement());

                    fs->traverseToParentElement();
                }

                fs->traverseToParentElement();
            }

            if (fs->traverseToElement("Monsters")) {
                if (fs->traverseToChildElement()) {

                    do {

                        if (fs->getAttribute("id", tempInt)) {

                            monsters.push_back(tempInt);
                        }

                    } while (fs->traverseToSyblingElement());

                    fs->traverseToParentElement();
                }

                fs->traverseToParentElement();
            }

            if (fs->traverseToElement("NPCs")) {
                if (fs->traverseToChildElement()) {

                    do {

                        if (fs->getAttribute("id", tempInt)) {

                            npcs.push_back(tempInt);
                        }

                    } while (fs->traverseToSyblingElement());

                    fs->traverseToParentElement();
                }

                fs->traverseToParentElement();
            }

            if (fs->traverseToElement("Connections")) {
                if (fs->traverseToChildElement()) {

                    do {

                        if (fs->getAttribute("name", tempStr) && fs->getAttribute("access", tempBool)) {

                            zone->addZoneConnection(tempStr, tempBool);
                        }

                    } while (fs->traverseToSyblingElement());
                }
            }

            // Now create all the ids that were loaded
            if (items.size() > 0 || interactables.size() > 0 || monsters.size() > 0 || npcs.size() > 0 || corpse.size() > 0) {

                std::list<int>::iterator iter;

                for (iter = items.begin(); iter != items.end(); iter++) {

                    zone->addItem(gom->newItem(*iter));
                }

                for (iter = interactables.begin(); iter != interactables.end(); iter++) {

                    zone->addInteractable(gom->newInteractable(*iter));
                }

                for (iter = monsters.begin(); iter != monsters.end(); iter++) {

                    zone->addMonster(gom->newMonster(*iter));
                }

                for (iter = npcs.begin(); iter != npcs.end(); iter++) {

                    zone->addNPC(gom->newNPC(*iter));
                }
            }
            
            if (corpse.size() > 0) {

                Corpse *corpseItem = new Corpse();

                for (std::list<int>::iterator iter = corpse.begin(); iter != corpse.end(); iter++) {

                    corpseItem->addItemID(*iter);
                }

                zone->addItem(corpseItem);
            }
        }

        return zone;
    }
    else {

        return NULL;
    }
}

// Load a zone from the current player save
Zone *SaveStateManager::loadZone(std::string &zoneName, std::string &saveName) {

    return this->loadZone(zoneName.c_str(), saveName.c_str());
}

// Save the zone details to the player temp save file
void SaveStateManager::saveZone(const char *playerName, Zone *zone) {

    FileSystem *fs = &FileSystem::Instance();

    if (fs->useFile(playerName)) {
        if (fs->traverseToElement("Zones")) {

            std::string tempName = zone->getName();
            const char *zoneName = NULL;

            for (unsigned int i = 0; i < tempName.length(); i++) {

                if (tempName[i] == ' ') {

                    tempName[i] = '_';
                }
            }

            zoneName = tempName.c_str();

            if (fs->traverseToElement(zoneName)) {

                fs->destroyCurrentElement();
            }

            if (fs->newElement(zoneName)) {

                if (fs->newElement("Description")) {

                    fs->setElementText(zone->zoneDescription);

                    fs->traverseToParentElement();
                }

                if (fs->newElement("Connections")) {

                    for (std::map<std::string, bool>::iterator iter = zone->connectedZones.begin();
                        iter != zone->connectedZones.end();
                        iter++) {

                        if (fs->newElement("Zone")) {

                            fs->setElementAttribute("name", (iter->first).c_str());
                            fs->setElementAttribute("access", iter->second);

                            fs->traverseToParentElement();
                        }
                    }

                    fs->traverseToParentElement();
                }

                if (zone->items.size() > 0) {
                    if (fs->newElement("Items")) {

                        for (std::map<std::string, Item *>::iterator iter = zone->items.begin();
                            iter != zone->items.end();
                            iter++) {

                            if (fs->newElement("Item")) {

                                fs->setElementAttribute("id", ((GameObject *)(iter->second))->getID());

                                if (((GameObject *)(iter->second))->getID() == CORPSE_ID) {

                                    Corpse *corpse = (Corpse *)iter->second;

                                    for (int id = corpse->getNextItemID(); id != NULL; id = corpse->getNextItemID()) {

                                        if (fs->newElement("Item")) {

                                            fs->setElementAttribute("id", id);

                                            fs->traverseToParentElement();
                                        }
                                    }
                                }

                                fs->traverseToParentElement();
                            }
                        }

                        fs->traverseToParentElement();
                    }
                }

                if (zone->interactables.size() > 0) {
                    if (fs->newElement("Interactables")) {

                        for (std::map<std::string, Interactable *>::iterator iter = zone->interactables.begin();
                            iter != zone->interactables.end();
                            iter++) {

                            if (fs->newElement("Interactable")) {

                                fs->setElementAttribute("id", ((GameObject *)(iter->second))->getID());

                                fs->traverseToParentElement();
                            }
                        }

                        fs->traverseToParentElement();
                    }
                }

                if (zone->monsters.size() > 0) {
                    if (fs->newElement("Monsters")) {

                        for (std::map<std::string, Monster *>::iterator iter = zone->monsters.begin();
                            iter != zone->monsters.end();
                            iter++) {

                            if (fs->newElement("Monster")) {

                                fs->setElementAttribute("id", ((GameObject *)(iter->second))->getID());

                                fs->traverseToParentElement();
                            }
                        }

                        fs->traverseToParentElement();
                    }
                }

                if (zone->npcs.size() > 0) {
                    if (fs->newElement("NPCs")) {

                        for (std::map<std::string, NPC *>::iterator iter = zone->npcs.begin();
                            iter != zone->npcs.end();
                            iter++) {

                            if (fs->newElement("NPC")) {

                                fs->setElementAttribute("id", ((GameObject *)(iter->second))->getID());

                                fs->traverseToParentElement();
                            }
                        }

                        fs->traverseToParentElement();
                    }
                }
            }
        }
    }
}

// Save the zone details to the player temp save file
void SaveStateManager::saveZone(std::string &playerName, Zone *zone) {

    this->saveZone(playerName.c_str(), zone);
}

// Save the game officially pushing it to a file
bool SaveStateManager::saveGame(Player *player) {

    if (player != NULL) {

        FileSystem *fs = &FileSystem::Instance();

        if (fs->useFile(player->getName())) {

            std::string saveFile = "../saves/" + player->getName() + ".soul";

            if (fs->traverseToElement("Player")) {
                
                fs->setElementAttribute("health", player->getHealth());
                fs->setElementAttribute("zone", player->getCurrentZone().c_str());

                if (fs->traverseToElement("Inventory")) {

                    fs->destroyCurrentElement();
                }

                if (fs->newElement("Inventory")) {

                    for (std::map<std::string, Item *>::iterator iter = player->inventory.begin();
                        iter != player->inventory.end();
                        iter++) {

                        GameObject *obj = (GameObject *)iter->second;

                        fs->newElement("Item");
                        fs->setElementAttribute("id", obj->getID());

                        fs->traverseToParentElement();
                    }
                }
            }

            if (fs->saveFile(player->getName(), saveFile)) {

                return true;
            }
        }
    }

    return false;
}
