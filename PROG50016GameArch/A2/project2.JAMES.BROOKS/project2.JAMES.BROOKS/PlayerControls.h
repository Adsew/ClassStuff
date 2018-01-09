#ifndef PLAYER_CONTROLS_H
#define PLAYER_CONTROLS_H

/*
Student: James Brooks
Class: Game Architecture

File: PlayerControls.h

Class: PlayerControls

Description: Component allowing input from the keyboard to move the player accordingly.
*/


#include "Component.h"


class Terrain;


class PlayerControls : public Component {

    REGISTER_COMPONENT(PlayerControls);

    
    /***** Variables *****/

private:

    float deltaTimeInput;
    float deltaTimeBomb;

protected:

    std::list<GameObject *> activeBombs;

    Terrain *map;

    int posX, posY;

    unsigned int bombPoolID;

    float bombInterval;


    /***** Functions *****/

protected:
    
    PlayerControls(unsigned int uniqueID);

    PlayerControls(unsigned int uniqueID, const char *type);
    
    ~PlayerControls();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;

    void setMap(Terrain *m);

    void setPosition(int x, int y);

    void setBombPool(unsigned int id);
};

#endif // !PLAYER_CONTROLS_H
