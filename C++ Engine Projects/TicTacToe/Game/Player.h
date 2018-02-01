#ifndef PLAYER_H
#define PLAYER_H

/*
Student: James Brooks
Class: Game Architecture

File: Player.h

Class: Player

Description: Base class for a player of tictactoe
*/


#include "Component.h"


class Asset;


class Player : public Component {

    REGISTER_ABSTRACT_COMPONENT(Player);


    /***** Variables *****/

public:

    std::shared_ptr<Asset> myPeice;

    bool human;

    bool myTurn;


    /***** Functions *****/

private:

    bool aiDecideMove(char *board);

    bool humanDecideMove(char *board);

protected:

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;

    bool takeTurn(char *board);
};


#endif // !PLAYER_H
