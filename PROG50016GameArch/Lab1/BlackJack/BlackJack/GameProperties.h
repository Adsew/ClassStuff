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
#define DOUBLE_DOWN 3

#define END_NO_REASON 0
#define PLAYER_WIN 1
#define DEALER_WIN 2
#define PUSH_DRAW 3


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
    int dHandVal;
    int dHandTrueVal;


    /***** Functions *****/

        /***** Support Functions *****/

    void startNewRound();   // Return most values to fresh round values

    int countHand(std::vector<Card> hand, bool countHidden);  // Get the count of the given hand

    int endRound();         // Draw for the deal until a winner is determined, handle bets, end round

public:

        /***** Main Runtime Functions *****/

    GameProperties();
    
    int init();         // Initialize game to be ready for first turn.

    int run();          // Main game loop processing turns and the mediator of i/o.

    int shutdown();     // Clean any required memory and end the game.
};