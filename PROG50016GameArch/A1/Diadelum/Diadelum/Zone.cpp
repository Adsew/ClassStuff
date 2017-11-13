/*
Student: James Brooks
Class: Game Architecture

File: Zone.cpp

Class: Zone

Description: Holds all information and can be interacted with for
any zone. Information contained is generally dynamic depending
on the zone's specific details.
*/


#include "Player.h"
#include "Interactable.h"
#include "Item.h"
#include "Monster.h"
#include "Zone.h"


Zone::Zone(std::string n)
    : Object(n) {

    zoneToMoveTo = "";

    movingFlag = false;
    modified = false;

    zoneDescription = "You are alone in a dark field with nothing around you but the feint smell of rotting corpses and burning buildings."
        " You see a rock, a potion of awesome, and an enemy called scary guy. Bitch town is in the distance and your future is blocked."
        "What do you do?";

    monsters["scary guy"] = new Monster(100, "scary guy");
    monsters["scary guy"]->setDescription("It looks like he hates nerds.");
    connectedZones["bitch town"] = true;
    connectedZones["my future"] = false;
    items["potion of awesome"] = new Item(200, "potion of awesome");
    items["potion of awesome"]->setDescription("A magical potion that eats people.");
    items["potion of awesome"]->setNumUses(1);
    items["potion of awesome"]->setLocationToUnlock("my future");
    items["potion of awesome"]->setWorksWithID(300);
    items["potion of awesome"]->setOnUseMsg("The potion desolves the rock.");
    interactables["rock"] = new Interactable(300, "rock");
    interactables["rock"]->setDescription("An ordinary rock.");
    interactables["rock"]->setNumUses(1);
    interactables["rock"]->setLocationToUnlock("my future");
    interactables["rock"]->setWorksWithID(200);
    interactables["rock"]->setOnUseMsg("You smash the potion with the rock, also moving the rock out of the way...");
}


Zone::~Zone() {

    delete monsters["scary guy"];
    delete items["potion of awesome"];
    delete interactables["rock"];
}

void Zone::update() {

    // Check for anything that needs to be deleted from the scene

    std::map<std::string, Interactable *>::iterator interIter = interactables.begin();

    while (interIter != interactables.end()) {

        if (interIter->second->getNeedsDeletion()) {

            delete interIter->second;
            interIter->second = NULL;
            interIter = interactables.erase(interIter);
        }
        else {

            interIter++;
        }
    }

    std::map<std::string, Item *>::iterator itemIter = items.begin();

    while (itemIter != items.end()) {

        if (itemIter->second->getNeedsDeletion()) {

            delete itemIter->second;
            itemIter->second = NULL;
            itemIter = items.erase(itemIter);
        }
        else {
            itemIter++;
        }
    }

    std::map<std::string, Monster *>::iterator monIter = monsters.begin();

    while (monIter != monsters.end()) {

        if (monIter->second->getNeedsDeletion()) {

            delete monIter->second;
            monIter->second = NULL;
            monIter = monsters.erase(monIter);
        }
        else {

            monIter++;
        }
    }
}


// Action functions

void Zone::noAction(std::list<std::pair<int, std::string>> &action) {

    messageToP = "I don't know how to";

    for (std::list<std::pair<int, std::string>>::iterator iter = action.begin();
        iter != action.end();
        iter++) {

        messageToP += " " + (*iter).second;
    }

    messageToP += ".";
}

void Zone::move(std::list<std::pair<int, std::string>> &action) {

    std::list<std::pair<int, std::string>>::iterator actionItem = action.begin();

    messageToP = "";

    actionItem++;

    if (action.size() <= 2) {

        if (actionItem != action.end()) {

            try {
                if (connectedZones.at((*actionItem).second)) {

                    movingFlag = true;
                    zoneToMoveTo = (*actionItem).second;
                }
                else {

                    messageToP = "I can't go to " + (*actionItem).second + " right now.";
                }
            }
            catch (const std::out_of_range &ex) {

                messageToP = "I don't quite understand where that is.";
            }
        }
        // Move without giving where to
        else {

            messageToP = "Hmm... Where should I go?";
        }
    }
    // Too many actions typed in one line
    else {

        messageToP = "I can only do so many things at once!";
    }
}

void Zone::use(std::list<std::pair<int, std::string>> &action) {

    std::list<std::pair<int, std::string>>::iterator actionItem = action.begin();

    messageToP = "";

    actionItem++;

    if (action.size() == 2 || action.size() == 4) {

        if (actionItem != action.end()) {

            GameObject *useItem1 = NULL;
            GameObject *useItem2 = NULL;

            // Find what the player is trying to use
            try {
                useItem1 = interactables.at((*actionItem).second);
            }
            catch (const std::out_of_range &ex) {

                try {
                    useItem1 = items.at((*actionItem).second);
                }
                catch (const std::out_of_range &ex) {

                    try {
                        useItem1 = monsters.at((*actionItem).second);
                    }
                    catch (const std::out_of_range &ex) {

                        try {
                            useItem1 = (*player).inventory.at((*actionItem).second);
                        }
                        catch (const std::out_of_range &ex) {

                            messageToP = "I can't find what you want me to use.";
                        }
                    }
                }
            }

            // Check for second use with item if size was = 4
            actionItem++;

            if (actionItem != action.end() && useItem1 != NULL) {
                if ((*actionItem).first == 9) {

                    actionItem++;

                    try {
                        useItem2 = interactables.at((*actionItem).second);
                    }
                    catch (const std::out_of_range &ex) {

                        try {
                            useItem2 = items.at((*actionItem).second);
                        }
                        catch (const std::out_of_range &ex) {

                            try {
                                useItem2 = monsters.at((*actionItem).second);
                            }
                            catch (const std::out_of_range &ex) {

                                try {
                                    useItem2 = (*player).inventory.at((*actionItem).second);
                                }
                                catch (const std::out_of_range &ex) {

                                    messageToP = "I can't find what you want me to use " + messageToP + " with.";
                                }
                            }
                        }
                    }
                }
                // Didn't say with, but another command
                else {

                    messageToP = "I can only do so many things at once!";
                }
            }

            // Single use item
            if (useItem1 != NULL && action.size() == 2) {

                messageToP = useItem1->use();

                // If either of the following work, the item was used correctly
                try {

                    connectedZones.at(useItem1->unlockLocation()) = true;
                }
                catch (const std::out_of_range &ex) {}

                try {

                    useItem1->dropItem();           // CREATE ITEM TO ADD TO PLAYER INVENTORY HERE
                }
                catch (const std::out_of_range &ex) {}

                useItem1->setInUse(false);
            }
            // Use item with another item
            else if (useItem1 != NULL && useItem2 != NULL && action.size() == 4) {

                messageToP = useItem1->useWith(useItem2);

                // If either of the following work, the item was used correctly
                try {
                    connectedZones.at(useItem2->unlockLocation()) = true;
                }
                catch (const std::out_of_range &ex) {}

                try {

                    useItem2->dropItem();           // CREATE ITEM TO ADD TO PLAYER INVENTORY HERE
                }
                catch (const std::out_of_range &ex) {}

                useItem1->setInUse(false);
                useItem2->setInUse(false);
            }
        }
        // Use without an item to use
        else {

            messageToP = "What should I be using?";
        }
    }
    // Too many actions typed in one line
    else {

        messageToP = "I can only do so many things at once!";
    }
}

void Zone::search(std::list<std::pair<int, std::string>> &action) {

    std::list<std::pair<int, std::string>>::iterator actionItem = action.begin();

    messageToP = "";

    actionItem++;

    if (action.size() <= 2) {

        if (actionItem != action.end()) {

            // Find what is being looked at through everything in the zone
            try {
                messageToP = interactables.at((*actionItem).second)->lookat();
            }
            catch (const std::out_of_range &ex) {

                try {
                    messageToP = items.at((*actionItem).second)->lookat();
                }
                catch (const std::out_of_range &ex) {

                    try {
                        messageToP = monsters.at((*actionItem).second)->lookat();
                    }
                    catch (const std::out_of_range &ex) {

                        messageToP = "I dont see that anywhere.";
                    }
                }
            }
        }
        // Just said search non-specifically
        else {

            if (interactables.size() > 0 || items.size() > 0 || monsters.size() > 0){
                
                messageToP = "There are definitly things around here.";
            }
            else {

                messageToP = "Not much more for me to do around here.";
            }
        }
    }
    // Too many actions typed in one line
    else {

        messageToP = "I can only do so many things at once!";
    }
}

void Zone::pickup(std::list<std::pair<int, std::string>> &action) {

    std::list<std::pair<int, std::string>>::iterator actionItem = action.begin();

    messageToP = "";

    actionItem++;

    if (action.size() <= 2) {

        if (actionItem != action.end()) {

            try {
                // Transfering to inventory
                Item *itemInScene = items.at((*actionItem).second);
                items.erase((*actionItem).second);
                player->inventory[(*actionItem).second] = itemInScene;

                messageToP = "Obtained " + itemInScene->getName() + ".";
            }
            catch (const std::out_of_range &ex) {

                messageToP = "I dont see any " + (*actionItem).second + "s anywhere.";
            }
        }
        else {

            messageToP = "What am I supposed to pick up?";
        }
    }
    else {

        messageToP = "I can only do so many things at once!.";
    }
}

void Zone::attack(std::list<std::pair<int, std::string>> &action) {

    std::list<std::pair<int, std::string>>::iterator actionItem = action.begin();

    messageToP = "";

    actionItem++;

    if (action.size() <= 2) {

        if (actionItem != action.end()) {

            try {
                messageToP = monsters.at((*actionItem).second)->attack(player);
            }
            catch (const std::out_of_range &ex) {

                messageToP = "I can't attack what isn't there.";
            }
        }
        else {

            messageToP = "I swing my arms around with wreckless abandon.";
        }
    }
    else {

        messageToP = "I can only do so many things at once!.";
    }
}

void Zone::help() {

    messageToP = "You can: 'go', 'use', 'use __ with __', 'look at', 'attack', 'save', and 'exit'.";
}

std::string Zone::render() {

    return "\n" + zoneDescription + "\n\n" + messageToP;
}


    // Accessors

bool Zone::setDescription(const char *desc) {

    zoneDescription = desc;
}

bool Zone::setDescription(std::string &desc) {

    return this->setDescription(desc.c_str());
}

bool Zone::addInteractable(Interactable *inter) {

    if (inter != NULL) {

        interactables[inter->getName()] = inter;

        return true;
    }

    return false;
}

bool Zone::addItem(Item *item) {

    if (item != NULL) {

        items[item->getName()] = item;

        return true;
    }

    return false;
}

bool Zone::addMonster(Monster *mon) {

    if (mon != NULL) {

        monsters[mon->getName()] = mon;

        return true;
    }

    return false;
}

bool Zone::addZoneConnection(std::string &zoneName, bool accessable) {

    if (zoneName.length() > 0) {

        connectedZones[zoneName] = accessable;

        return true;
    }

    return false;
}

bool Zone::setPlayer(Player *p) {

    player = p;
}

bool Zone::movingFlagStatus() {

    return movingFlag;
}

std::string &Zone::getZoneToMoveTo() {

    return zoneToMoveTo;
}
