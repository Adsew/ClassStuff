/*
Student: James Brooks
Class: Game Architecture

File: GameObjectMaker.cpp

Class: GameObjectMaker

Description: A singleton class that produces the desired game object
with the helpf of the file system for loading the information.
*/


#include <list>

#include "FileSystem.h"
#include "Interactable.h"
#include "Item.h"
#include "Monster.h"
#include "Zone.h"
#include "GameObjectMaker.h"


GameObjectMaker::GameObjectMaker() {}

GameObjectMaker::GameObjectMaker(GameObjectMaker &gom) {}

GameObjectMaker::~GameObjectMaker() {}

GameObjectMaker &GameObjectMaker::operator=(GameObjectMaker &gom) { return gom; }

Item *GameObjectMaker::newItem(int id) {

    FileSystem *fs = &FileSystem::Instance();
    Item *item = NULL;

    fs->useFile("items");
    fs->traverseToElement("Items");
    
    // Traverse to the desired item, load all attributes as available
    if (fs->traverseToElement("I" + id)) {

        std::string tempStr;
        int tempInt = 0;

        fs->getAttribute("name", tempStr);       // All required to have name

        item = new Item(id, tempStr);

        if (fs->getAttribute("uses", tempInt)) {

            item->setNumUses(tempInt);
        }

        if (fs->getAttribute("worksID", tempInt)) {

            item->setWorksWithID(tempInt);
        }

        if (fs->getAttribute("creates", tempInt)) {

            item->setCreatesID(tempInt);
        }

        if (fs->getAttribute("unlockLoc", tempStr)) {

            item->setLocationToUnlock(tempStr);
        }

        if (fs->traverseToElement("Description")) {

            if (fs->getElementText(tempStr)) {

                item->setDescription(tempStr);
            }

            if (fs->traverseToSyblingElement("UseText")) {

                if (fs->getElementText(tempStr)) {

                    item->setOnUseMsg(tempStr);
                }
            }

            if (fs->traverseToSyblingElement("ZoneText")) {

                if (fs->getElementText(tempStr)) {

                    item->setInZoneMsg(tempStr);
                }
            }
        }
    }

    return item;
}

Interactable *GameObjectMaker::newInteractable(int id) {

    FileSystem *fs = &FileSystem::Instance();
    Interactable *inter = NULL;

    fs->useFile("interactables");
    fs->traverseToElement("Interactables");

    // Traverse to the desired item, load all attributes as available
    if (fs->traverseToElement("E" + id)) {

        std::string tempStr;
        int tempInt = 0;

        fs->getAttribute("name", tempStr);       // All required to have name

        inter = new Interactable(id, tempStr);

        if (fs->getAttribute("uses", tempInt)) {

            inter->setNumUses(tempInt);
        }

        if (fs->getAttribute("worksID", tempInt)) {

            inter->setWorksWithID(tempInt);
        }

        if (fs->getAttribute("creates", tempInt)) {

            inter->setCreatesID(tempInt);
        }

        if (fs->getAttribute("unlockLoc", tempStr)) {

            inter->setLocationToUnlock(tempStr);
        }

        if (fs->traverseToElement("Description")) {

            if (fs->getElementText(tempStr)) {

                inter->setDescription(tempStr);
            }

            if (fs->traverseToSyblingElement("UseText")) {

                if (fs->getElementText(tempStr)) {

                    inter->setOnUseMsg(tempStr);
                }
            }

            if (fs->traverseToSyblingElement("ZoneText")) {

                if (fs->getElementText(tempStr)) {

                    inter->setInZoneMsg(tempStr);
                }
            }
        }
    }

    return inter;
}

Monster *GameObjectMaker::newMonster(int id) {

    FileSystem *fs = &FileSystem::Instance();
    Monster *mon = NULL;

    fs->useFile("monsters");
    fs->traverseToElement("Monsters");

    // Traverse to the desired item, load all attributes as available
    if (fs->traverseToElement("M" + id)) {

        std::string tempStr;
        int tempInt = 0;

        fs->getAttribute("name", tempStr);       // All required to have name

        mon = new Monster(id, tempStr);

        if (fs->getAttribute("uses", tempInt)) {

            mon->setNumUses(tempInt);
        }

        if (fs->getAttribute("worksID", tempInt)) {

            mon->setWorksWithID(tempInt);
        }

        if (fs->getAttribute("creates", tempInt)) {

            mon->setCreatesID(tempInt);
        }

        if (fs->getAttribute("unlockLoc", tempStr)) {

            mon->setLocationToUnlock(tempStr);
        }

        if (fs->traverseToElement("Description")) {

            if (fs->getElementText(tempStr)) {

                mon->setDescription(tempStr);
            }

            if (fs->traverseToSyblingElement("UseText")) {

                if (fs->getElementText(tempStr)) {

                    mon->setOnUseMsg(tempStr);
                }
            }

            if (fs->traverseToSyblingElement("ZoneText")) {

                if (fs->getElementText(tempStr)) {

                    mon->setInZoneMsg(tempStr);
                }
            }
        }
    }

    return mon;
}

Zone *GameObjectMaker::newZone(const char *name) {

    FileSystem *fs = &FileSystem::Instance();
    Zone *zone = NULL;
    std::string tempName = name;

    for (unsigned int i = 0; i < tempName.length(); i++) {

        if (tempName[i] == ' ') {

            tempName[i] = '_';
        }
    }

    name = tempName.c_str();

    fs->useFile("map");
    fs->traverseToElement("Zones");

    // Zone exists, begin to load details
    if (fs->traverseToElement(name)) {

        std::list<int> items;
        std::list<int> interactables;
        std::list<int> monsters;
        std::string tempStr;
        int tempInt = 0;
        bool tempBool = true;

        zone = new Zone(name);

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

                        items.push_back(tempInt);
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
        if (items.size() > 0 || interactables.size() > 0 || monsters.size() > 0) {

            std::list<int>::iterator iter;

            for (iter = items.begin(); iter != items.end(); iter++) {

                zone->addItem(this->newItem(*iter));
            }

            for (iter = interactables.begin(); iter != interactables.end(); iter++) {

                zone->addInteractable(this->newInteractable(*iter));
            }

            for (iter = monsters.begin(); iter != monsters.end(); iter++) {

                zone->addMonster(this->newMonster(*iter));
            }
        }
    }

    return zone;
}

Zone *GameObjectMaker::newZone(std::string &name) {

    return this->newZone(name.c_str());
}
