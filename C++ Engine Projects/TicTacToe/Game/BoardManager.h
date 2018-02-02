#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: BoardManager.h

Class: BoardManager

Description: Controls the board and manages the aplyer's turns.
*/


#include "Component.h"


class Player;


class BoardManager : public Component {

    REGISTER_COMPONENT(BoardManager);


    /***** Variables *****/

    Player *players[2];

    bool player1sTurn;


    /***** Functions *****/

protected:

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;
};

#endif // !BOARD_MANAGER_H
