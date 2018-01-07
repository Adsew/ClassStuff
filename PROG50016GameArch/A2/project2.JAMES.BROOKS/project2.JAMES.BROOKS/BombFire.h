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


class BombFire : public Component {

    REGISTER_COMPONENT(BombFire);


    /***** Variables *****/




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
};

#endif // !BOMB_FIRE_H
