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
#include "Zone.h"


Zone::Zone(std::string n, Player *p)
    : Object(n) {

    player = p;

    zoneToMoveTo = "";

    movingFlag = false;
    modified = false;

    zoneDescription = "You are alone in a dark field with nothing around you but the feint smell of rotting corpses and burning buildings."
        " You see a rock, a potion of awesome, and an enemy called scary guy. Bitch town is in the distance and your future is blocked."
        "What do you do?";

    monsters["scary guy"] = "It looks like he hates nerds.";
    connectedZones["bitch town"] = true;
    connectedZones["my future"] = false;
    items["potion of awesome"] = "A magical potion that eats people.";
    interactables["rock"] = "An ordinary rock.";
}


Zone::~Zone() {


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

            // Find what the player is trying to use
            try {
                messageToP = interactables.at((*actionItem).second);
            }
            catch (const std::out_of_range &ex) {

                try {
                    messageToP = items.at((*actionItem).second);
                }
                catch (const std::out_of_range &ex) {

                    try {
                        messageToP = monsters.at((*actionItem).second);
                    }
                    catch (const std::out_of_range &ex) {

                        /*try {
                            messageToP = (*player).inventory.at((*actionItem).second);
                        }
                        catch (const std::out_of_range &ex) {*/

                            messageToP = "I can't find what you want me to use.";
                        //}
                    }
                }
            }

            // Check for second use with item if size was = 4
            actionItem++;

            if (actionItem != action.end() && messageToP != "I can't find what you want me to use.") {
                if ((*actionItem).first == 8) {

                    actionItem++;

                    try {
                        messageToP += interactables.at((*actionItem).second);
                    }
                    catch (const std::out_of_range &ex) {

                        try {
                            messageToP += items.at((*actionItem).second);
                        }
                        catch (const std::out_of_range &ex) {

                            try {
                                messageToP += monsters.at((*actionItem).second);
                            }
                            catch (const std::out_of_range &ex) {

                                /*try {
                                messageToP += (*player).inventory.at((*actionItem).second);
                                }
                                catch (const std::out_of_range &ex) {*/

                                messageToP = "I can't find what you want me to use " + messageToP + " with.";
                                //}
                            }
                        }
                    }
                }
                // Didn't say with, but another command
                else {

                    messageToP = "I can only do so many things at once!";
                }
            }

            // When game objects implemented and loaded, check if use 1 and 2 
            // are there and call use function or use with function on the items here
            // Remember to change if statement whether message was set for first item
            // when checking if we should even look for a second item


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
                messageToP = interactables.at((*actionItem).second);
            }
            catch (const std::out_of_range &ex) {

                try {
                    messageToP = items.at((*actionItem).second);
                }
                catch (const std::out_of_range &ex) {

                    try {
                        messageToP = monsters.at((*actionItem).second);
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

void Zone::attack(std::list<std::pair<int, std::string>> &action) {

    messageToP = "CHAARGE!!!!!";
}

void Zone::help() {

    messageToP = "You can: 'go', 'use', 'use __ with __', 'look at', 'attack', 'save', and 'exit'.";
}

std::string Zone::render() {

    return "\n" + zoneDescription + "\n\n" + messageToP;
}


    // Accessors

bool Zone::movingFlagStatus() {

    return movingFlag;
}

std::string &Zone::getZoneToMoveTo() {

    return zoneToMoveTo;
}
