#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObject.h

Class: GameObject

Description: A game object to be used to represent objects within the game world.
*/


#include <map>

#include "Object.h"


class GameObject : public Object {

protected:

    /***** Variables *****/

    int id;

    bool needsDeletion;

    std::string description;

    bool inUse;
    int numUses;

    int worksWithID;    // A game object that can be used with this
    int createsID;      // If another game object is produced when this is used
    std::string locationToUnlock;   // If unlocks a new direction to go
    std::string onUseMsg;

public:

    /***** Functions *****/

    GameObject();

    GameObject(int idNum, std::string &n);

    virtual ~GameObject();

    // Cycle update for game object
    virtual void update();

        // Interactivity functions

    virtual std::string use() = 0;

    virtual std::string useWith(GameObject *go) = 0;

    virtual std::string lookat() = 0;

    int dropItem();

    std::string unlockLocation();

        // Accessors

    int getID();

    void setNeedsDeletion(bool b);

    bool getNeedsDeletion();

    void setDescription(std::string &desc);

    void setDescription(const char *desc);

    void setInUse(bool b);

    bool getInUse();

    void setNumUses(int n);

    int getNumUses();

    void setWorksWithID(int otherItemID);

    void setCreatesID(int itemToCreate);

    void setLocationToUnlock(std::string &loc);

    void setLocationToUnlock(const char *loc);

    void setOnUseMsg(std::string &msgWhenUsed);

    void setOnUseMsg(const char *msgWhenUsed);
};

#endif
