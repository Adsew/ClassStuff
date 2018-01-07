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


class Bomb : public Component {

    REGISTER_COMPONENT(Bomb);


    /***** Variables *****/




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
};

#endif // !BOMB_H
