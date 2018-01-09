#ifndef BOMB_H
#define BOMB_H

/*
Student: James Brooks
Class: Game Architecture

File: Bomb.h

Class: Bomb

Description: Represents an object that will detonate after a set time.
*/


#include "Component.h"


class AnimatedSprite;
class Terrain;


class Bomb : public Component {

    REGISTER_COMPONENT(Bomb);


    /***** Variables *****/

protected:

    AnimatedSprite *anim;
    Terrain *map;

    int posX, posY;

    bool exploded;

public:

    GameObject *owner;


    /***** Functions *****/

protected:

    Bomb(unsigned int uniqueID);

    Bomb(unsigned int uniqueID, const char *type);

    ~Bomb();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;

    // Reset the bomb to a pre-exploded state
    void resetBomb();

    // Place the bomb at the given location in the map
    void placeAtMe(Terrain *terrain, int x, int y);

    // Check if the bomb has exploded and needs deactivation
    bool isExploded();
};

#endif // !BOMB_H
