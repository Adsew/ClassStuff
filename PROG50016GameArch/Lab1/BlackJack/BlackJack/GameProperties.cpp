/*
File: GameProperties.cpp

Class: GameProperties

Description: Class responsible for maintaining the properties/values of the
    current execution of the game. Due to the size of the game it also handles
    functions for running the game.
*/


#include "GameProperties.h"
#include <iostream>

/***** Constructor *****/

GameProperties::GameProperties() {

    isRunning = false;
}


/***** Functions *****/

// Initialize game to be ready for first turn.
int GameProperties::init() {

    currentBet = 0;
    pCurrency = 500;
    dHandVal = 0;
    pHandVal = 0;
    pHandSplit = 0;


    // Get player input to set up the game
    isRunning = screen.runTitleScreen();
    
    return isRunning;
}

// Main game loop processing turns and the mediator of i/o.
int GameProperties::run() {

    int choice = 0;

    while (isRunning){
        
        // Start with the initial bid then deal the first cards
        currentBet = screen.runBetting(pCurrency);
        
        screen.runGameDisplay(currentBet);

        if (choice == HIT) {


        }
        else if (choice == STAND) {


        }
        else { // Double only other choice


        }

        isRunning = false;
    }

    return 1;
}

// Clean any required memory and end the game.
int GameProperties::shutdown() {

    screen.runExitScreen();

    return 1;
}
