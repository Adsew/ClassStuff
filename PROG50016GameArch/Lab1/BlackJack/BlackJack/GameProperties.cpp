/*
File: GameProperties.cpp

Class: GameProperties

Description: Class responsible for maintaining the properties/values of the
    current execution of the game. Due to the size of the game it also handles
    functions for running the game.
*/


#include "GameProperties.h"


/***** Constructor *****/

GameProperties::GameProperties() {

    isRunning = false;
}


/***** Functions *****/

// Initialize game to be ready for first turn.
int GameProperties::init() {

    currentBet = 0;
    pCurrency = 500;
    dHand = 0;
    pHand = 0;
    pHandSplit = 0;


    // Get player input to set up the game
    isRunning = screen.runTitleScreen();

    return isRunning;
}

// Main game loop processing turns and the mediator of i/o.
int GameProperties::run() {



    return 1;
}

// Clean any required memory and end the game.
int GameProperties::shutdown() {

    screen.exitScreen();

    isRunning = false;

    return 1;
}
