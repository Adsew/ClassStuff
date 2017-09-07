#pragma once

/*
File: GameProperties.h

Class: GameProperties

Description: Class responsible for maintaining the properties/values of the
current execution of the game. Due to the size of the game it also handles
functions for running the game.
*/


#include <vector>

#include "BlackJackIO.h"
#include "Deck.h"


/***** Definitions *****/

#define HIT 1
#define STAND 2
#define DOUBLE 3

class GameProperties {

private:


    /***** Variables *****/

        /* Engine Variables */

    BlackjackIO screen;
    bool isRunning;

        /* Games Variables */

    Deck deck;
    std::vector<Card> pHand;
    std::vector<Card> dHand;
    int currentBet;
    int pCurrency;
    int pHandVal;
    int pHandSplit;
    int dHandVal;

public:

    /***** Functions *****/

    GameProperties();
    
    int init();         // Initialize game to be ready for first turn.

    int run();          // Main game loop processing turns and the mediator of i/o.

    int shutdown();     // Clean any required memory and end the game.
};