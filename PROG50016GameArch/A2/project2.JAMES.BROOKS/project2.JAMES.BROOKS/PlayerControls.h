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


class PlayerControls : public Component {

    REGISTER_COMPONENT(PlayerControls)


    /***** Functions *****/

protected:
    
    PlayerControls(unsigned int uniqueID);
    
    ~PlayerControls();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;
};

#endif // !PLAYER_CONTROLS_H
