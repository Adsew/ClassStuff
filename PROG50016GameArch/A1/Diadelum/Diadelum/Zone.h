#ifndef ZONE_H
#define ZONE_H

/*
Student: James Brooks
Class: Game Architecture

File: Zone.h

Class: Zone

Description: Holds all information and can be interacted with for
    any zone. Information contained is generally dynamic depending
    on the zone's specific details.
*/


#include <list>
#include <map>

#include "IRenderable.h"
#include "Object.h"


class Player;
class Interactable;
class Items;
class Monster;
class NPC;


class Zone : public Object, public IRenderable {

private:

    /***** Variables *****/

    Player *player;

    std::map<std::string, bool> connectedZones;             // bool determines if accessable or not
    std::map<std::string, Interactable *> interactables;    // Environment interactables
    std::map<std::string, Item *> items;                    // Pickupable items in the zone
    std::map<std::string, Monster *> monsters;              // Monsters in the area
    std::map<std::string, NPC *> npcs;                      // NPCs in the area available for talk and interaction

    std::string messageToP;
    std::string zoneDescription;

    std::string zoneToMoveTo;
    bool movingFlag;

    bool modified;

protected:

    /***** Functions *****/

    virtual std::string render();

public:

    Zone(std::string n);

    virtual ~Zone();

    void update();

    // Actions

    void noAction(std::list<std::pair<int, std::string>> &action);

    void move(std::list<std::pair<int, std::string>> &action);

    void use(std::list<std::pair<int, std::string>> &action);

    void search(std::list<std::pair<int, std::string>> &action);

    void pickup(std::list<std::pair<int, std::string>> &action);

    void talk(std::list<std::pair<int, std::string>> &action);

    void attack(std::list<std::pair<int, std::string>> &action);

    void help();

    // Accessors

    bool setDescription(const char *desc);

    bool setDescription(std::string &desc);

    bool addInteractable(Interactable *inter);

    bool addItem(Item *item);

    bool addMonster(Monster *mon);

    bool addNPC(NPC *npc);

    bool addZoneConnection(std::string &zoneName, bool accessable);

    bool setPlayer(Player *p);

    bool movingFlagStatus();

    std::string &getZoneToMoveTo();
};

#endif
