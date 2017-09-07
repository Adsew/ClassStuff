#pragma once

/*
File: GameProperties.h

Class: GameProperties

Description: Class responsible for maintaining the properties/values of the
current execution of the game. Due to the size of the game it also handles
functions for running the game.
*/


#include "Deck.h"


class GameProperties {

private:


    /***** Variables *****/

    Deck deck;

        /* Engine Variables */

    bool isRunning;

        /* Games Variables */

    int currentBet;
    int pCurrency;
    int pHand;
    int pHandSplit;
    int dHand;


    /***** Functions *****/




public:

    GameProperties();
    
    int init();         // Initialize game to be ready for first turn.

    int run();          // Main game loop processing turns and the mediator of i/o.

    int shutdown();     // Clean any required memory and end the game.
};