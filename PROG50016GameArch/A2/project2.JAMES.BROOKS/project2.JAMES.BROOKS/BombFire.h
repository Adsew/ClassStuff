#ifndef BOMB_FIRE_H
#define BOMB_FIRE_H

/*
Student: James Brooks
Class: Game Architecture

File: BombFire.h

Class: BombFire

Description: Spawned by a bomb after it detonates and kills enemies and players it touches.
*/


#include "Component.h"


class Terrain;


class BombFire : public Component {

    REGISTER_COMPONENT(BombFire);


    /***** Variables *****/

    Terrain *map;
    GameObject *owner;  // Who spawned the bomb

    int posX, posY;

    float deathTimer;
    float timeTilDeath;


    /***** Functions *****/

protected:

    BombFire(unsigned int uniqueID);

    BombFire(unsigned int uniqueID, const char *type);

    ~BombFire();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;

    // Set the map the fire is on
    void setMap(Terrain *t, int x, int y);

    // Set the owner of who spawned the bomb
    void setOwner(GameObject *o);
};

#endif // !BOMB_FIRE_H
