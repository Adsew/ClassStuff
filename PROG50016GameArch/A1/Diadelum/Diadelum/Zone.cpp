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
#include "Corpse.h"
#include "Monster.h"
#include "NPC.h"
#include "InputCodes.h"
#include "GameObjectMaker.h"
#include "Zone.h"


Zone::Zone(std::string n)
    : Object(n) {

    player = NULL;

    zoneToMoveTo = "";

    movingFlag = false;
    modified = false;

    zoneDescription = "";
    messageToP = "";
}


Zone::~Zone() {

    std::map<std::string, Interactable *>::iterator interIter = interactables.begin();

    while (interIter != interactables.end()) {

        delete interIter->second;
        interIter->second = NULL;
        interIter = interactables.erase(interIter);
    }

    std::map<std::string, Item *>::iterator itemIter = items.begin();

    while (itemIter != items.end()) {

        delete itemIter->second;
        itemIter->second = NULL;
        itemIter = items.erase(itemIter);
    }

    std::map<std::string, Monster *>::iterator monIter = monsters.begin();

    while (monIter != monsters.end()) {

        delete monIter->second;
        monIter->second = NULL;
        monIter = monsters.erase(monIter);
    }

    std::map<std::string, NPC *>::iterator npcIter = npcs.begin();

    while (npcIter != npcs.end()) {

        delete npcIter->second;
        npcIter->second = NULL;
        npcIter = npcs.erase(npcIter);
    }
}

void Zone::update() {

    // Check for anything that needs to be deleted from the scene

    std::map<std::string, Interactable *>::iterator interIter = interactables.begin();

    while (interIter != interactables.end()) {

        if (interIter->second->getNeedsDeletion()) {

            delete interIter->second;
            interIter->second = NULL;
            interIter = interactables.erase(interIter);

            modified = true;
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

            modified = true;
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

            modified = true;
        }
        else {

            monIter++;
        }
    }

    std::map<std::string, NPC *>::iterator npcIter = npcs.begin();

    while (npcIter != npcs.end()) {

        if (npcIter->second->getNeedsDeletion()) {

            delete npcIter->second;
            npcIter->second = NULL;
            npcIter = npcs.erase(npcIter);

            modified = true;
        }
        else {

            npcIter++;
        }
    }

    // If player died, move him to the dream zone
    if (player->isDead()) {

        messageToP += " You have died.";

        addItem((Item *)player->restoreFromDeath());

        movingFlag = true;
        zoneToMoveTo = "inbetween";
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

    // Move code only requires "move" and "where" in the action
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

    // Action could be "use itemname" or "use itemname with itemname"
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
                            useItem1 = npcs.at((*actionItem).second);
                        }
                        catch (const std::out_of_range &ex) {

                            useItem1 = player->hasItem((*actionItem).second);   // Returns null if doesnt exist

                            if (useItem1 == NULL) {

                                messageToP = "I can't find what you want me to use.";
                            }
                        }
                    }
                }
            }

            // Check for second use with item if size was = 4 and ensure 3rd word was a connector
            actionItem++;

            if (actionItem != action.end() && useItem1 != NULL) {
                if ((*actionItem).first == IN_CODE_CONNECT) {

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
                                    useItem2 = npcs.at((*actionItem).second);
                                }
                                catch (const std::out_of_range &ex) {

                                    useItem2 = player->hasItem((*actionItem).second);

                                    if (useItem2 == NULL) {

                                        messageToP = "I can't find what you want me to use " + messageToP + " with.";
                                    }
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
                // GameObjects only unlock a location or drop item if used in the correct way
                try {

                    connectedZones.at(useItem1->unlockLocation()) = true;
                }
                catch (const std::out_of_range &ex) {}

                if (useItem1->dropItem() > 0) {

                    Item *drop = GameObjectMaker::Instance().newItem(useItem1->dropItem());

                    if (drop != NULL) {

                        player->addItemToInventory(drop);
                    }
                }

                useItem1->setInUse(false);  // End poroducing item results if was use was successful
            }
            // Use item with another item
            else if (useItem1 != NULL && useItem2 != NULL && action.size() == 4) {

                messageToP = useItem1->useWith(useItem2);

                // If either of the following work, the item was used correctly
                // GameObjects only unlock a location or drop item if used in the correct way

                // When using two things together, only ONE OBJECT will produce the results, 
                // determined by the items' useWith function
                try {
                    connectedZones.at(useItem1->unlockLocation()) = true;
                }
                catch (const std::out_of_range &ex) {}
                try {
                    connectedZones.at(useItem2->unlockLocation()) = true;
                }
                catch (const std::out_of_range &ex) {}

                if (useItem1->dropItem() > 0) {

                    Item *drop = GameObjectMaker::Instance().newItem(useItem1->dropItem());

                    player->addItemToInventory(drop);
                }
                else if (useItem2->dropItem() > 0) {

                    Item *drop = GameObjectMaker::Instance().newItem(useItem2->dropItem());

                    player->addItemToInventory(drop);
                }

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

    // Action should only be "search whattosearchfor"
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

                        try {
                            messageToP = npcs.at((*actionItem).second)->lookat();
                        }
                        catch (const std::out_of_range &ex) {

                            // Same thing, just different check for items in inventory
                            Item *tempItem = player->hasItem((*actionItem).second);

                            if (tempItem != NULL) {

                                messageToP = tempItem->lookat();
                            }
                            else {

                                messageToP = "I dont see that anywhere.";
                            }
                        }
                    }
                }
            }
        }
        // Just said search non-specifically
        else {

            if (interactables.size() > 0 || items.size() > 0 || monsters.size() > 0 || npcs.size() > 0){
                
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

    // Action should be "pickup whattopickup"
    if (action.size() <= 2) {

        if (actionItem != action.end()) {

            try {
                // Transfering to inventory
                Item *itemInScene = items.at((*actionItem).second);
                items[(*actionItem).second] = NULL;
                items.erase((*actionItem).second);
                player->addItemToInventory(itemInScene);

                modified = true;

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

void Zone::talk(std::list<std::pair<int, std::string>> &action) {

    std::list<std::pair<int, std::string>>::iterator actionItem = action.begin();

    messageToP = "";

    actionItem++;

    if (action.size() <= 2) {

        if (actionItem != action.end()) {

            try {
                
                messageToP = npcs.at((*actionItem).second)->talk();
            }
            catch (const std::out_of_range &ex) {

                messageToP = "I dont see any " + (*actionItem).second + "s to talk to.";
            }
        }
        else {

            messageToP = "Talking to myself isn't really helping right now.";
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
                Monster *atkMon = monsters.at((*actionItem).second);
                
                messageToP = atkMon->attack(player);

                try {
                    connectedZones.at(atkMon->unlockLocation()) = true;
                }
                catch (const std::out_of_range &ex) {}

                if (atkMon->dropItem() > 0) {

                    Item *drop = GameObjectMaker::Instance().newItem(atkMon->dropItem());

                    if (drop != NULL) {

                        messageToP += " Obtained " + drop->getName() + ".";
                    }

                    player->addItemToInventory(drop);
                }

                atkMon->setInUse(false);
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

    messageToP = "You can: 'go', 'use', 'use __ with __', 'look at', 'attack', 'talk to', 'save', and 'exit'.";
}

std::string Zone::render() {

    // Zone description first
    std::string output = "\n" + zoneDescription;

    // Then any identifiers for things in the zone
    std::map<std::string, Interactable *>::iterator interIter = interactables.begin();

    while (interIter != interactables.end()) {

        output += " " + interIter->second->getInZoneMsg();

        interIter++;
    }

    std::map<std::string, Item *>::iterator itemIter = items.begin();

    while (itemIter != items.end()) {

        output += " " + itemIter->second->getInZoneMsg();

        itemIter++;
    }

    std::map<std::string, Monster *>::iterator monIter = monsters.begin();

    while (monIter != monsters.end()) {

        output += " " + monIter->second->getInZoneMsg();

        monIter++;
    }

    std::map<std::string, NPC *>::iterator npcIter = npcs.begin();

    while (npcIter != npcs.end()) {

        output += " " + npcIter->second->getInZoneMsg();

        npcIter++;
    }

    // Finally message to player based on previous action
    return output + "\n\n" + messageToP;
}


    // Accessors

bool Zone::setDescription(const char *desc) {

    zoneDescription = desc;

    return true;
}

bool Zone::setDescription(std::string &desc) {

    return this->setDescription(desc.c_str());
}

bool Zone::setMessageToPlayer(const char *msg) {

    messageToP = msg;

    return true;
}

bool Zone::setMessageToPlayer(std::string &msg) {

    return this->setMessageToPlayer(msg.c_str());
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

bool Zone::addNPC(NPC *npc) {

    if (npc != NULL) {

        npcs[npc->getName()] = npc;

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

    if (p != NULL) {

        player = p;

        player->setCurrentZone(this->getName());

        return true;
    }
    
    return false;
}

bool Zone::movingFlagStatus() {

    return movingFlag;
}

std::string &Zone::getZoneToMoveTo() {

    return zoneToMoveTo;
}

void Zone::setModified(bool m) {

    modified = m;
}

bool Zone::getModified() {

    return modified;
}
