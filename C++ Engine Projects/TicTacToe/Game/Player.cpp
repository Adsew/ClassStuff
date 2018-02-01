/*
Student: James Brooks
Class: Game Architecture

File: Player.h

Class: Player

Description: Base class for a player of tictactoe
*/


#include "Core.h"

#include "AssetManager.h"
#include "Player.h"


IMPLEMENT_COMPONENT(Player);


bool Player::aiDecideMove(char *board) {

    return true;
}

bool Player::humanDecideMove(char *board) {

    return true;
}

void Player::initialize() {

    myPiece = NULL;

    myLetter = 'x';

    human = false;
    myTurn = false;
}

void Player::update() {


}

void Player::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    std::string pieceLetter = " ";

    if (FileSystem::Instance().getAttribute(accessor, "piece", pieceLetter)){

        myLetter = pieceLetter[0];

        if (myLetter == 'x') {

            myPiece = AssetManager::Instance().getAsset("XPieceTexture");
        }
        else if (myLetter == 'o') {

            myPiece = AssetManager::Instance().getAsset("OPieceTexture");
        }
    }

    FileSystem::Instance().getAttribute(accessor, "human", human);
}

Component &Player::operator=(const Component &comp) {

    const Player *orig = (const Player *)&comp;

    myPiece = orig->myPiece;
    myLetter = orig->myLetter;

    human = orig->human;

    return *this;
}

bool Player::takeTurn(char *board) {

    if (human) {

        return humanDecideMove(board);
    }
    
    return aiDecideMove(board);
}
