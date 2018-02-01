/*
Student: James Brooks
Class: Game Architecture

File: Player.h

Class: Player

Description: Base class for a player of tictactoe
*/


#include "Core.h"

#include "Player.h"


IMPLEMENT_ABSTRACT_COMPONENT(Player);


bool Player::aiDecideMove(char *board) {


}

bool Player::humanDecideMove(char *board) {


}

void Player::initialize() {

    human = false;
    myTurn = false;
}

void Player::update() {


}

void Player::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}

Component &Player::operator=(const Component &comp) {


}

bool Player::takeTurn(char *board) {

    if (human) {

        return humanDecideMove(board);
    }
    
    return aiDecideMove(board);
}
