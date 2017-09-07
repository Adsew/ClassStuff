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

// Get the count of the given hand, taking rules into account
int GameProperties::countHand(std::vector<Card> hand) {

    int count = 0, i = 0;
    bool hasAce = false;

    for (i = 0; i < hand.size; i++) {

        // Ace case, can only upscale 1 ace to 11 andyway, so use bool
        if (hand[i].getNumber() == 1) {

            hasAce = true;

            count = count + hand[i].getNumber();
        }
        // Royal card case
        else if (hand[i].getNumber() > 10) {

            count = count + 10;
        }
        else {

            count = count + hand[i].getNumber();
        }
    }

    // If you can remane under blackjack, count the ace as 11
    if (hasAce && count <= 11) {

        count = count + 10;
    }

    return count;
}

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

    Card c;
    int choice = 0;
    bool bustOccured = false;

    while (isRunning){
        
        // Start with the initial bid then deal the first cards
        currentBet = screen.runBetting(pCurrency);
        
        c = deck.draw();// ENSURE VALIDATION OF CARDS
        dHand.push_back(c);
        c = deck.draw();
        c.flip();
        dHand.push_back(c);

        c = deck.draw();
        c.flip();
        pHand.push_back(c);
        c = deck.draw();
        c.flip();
        pHand.push_back(c);

        screen.runGameDisplay(currentBet, pHand, dHand);

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
