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

    /***** Support Functions *****/

// Return most values to fresh round values
void GameProperties::startNewRound() {

    currentBet = 0;
    pHandVal = 0;
    dHandVal = 0;
    dHandTrueVal = 0;

    deck.restart();

    pHand.clear();
    dHand.clear();
}

// Get the count of the given hand, taking rules into account
int GameProperties::countHand(std::vector<Card> hand, bool countHidden = false) {

    int count = 0, i = 0;
    bool hasAce = false;

    for (i = 0; i < hand.size(); i++) {

        // Onlky count flipped cards (for dealer count)
        if (hand[i].getFlipped() || countHidden) {

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
    }

    // If you can remane under blackjack, count the ace as 11
    if (hasAce && count <= 11) {

        count = count + 10;
    }

    return count;
}

// Draw for the deal until a winner is determined, handle bets, end round
int GameProperties::endRound() {

    Card c;
    
    dHand[0].flip();        // Reveal dealers cards

    dHandVal = countHand(dHand);

    if (pHandVal > 21) {

        pCurrency = pCurrency - currentBet;
        currentBet = 0;

        return DEALER_WIN;
    }

    // 17 standard stand point
    while (dHandVal < 17) {

        c = deck.draw();
        c.flip();

        dHand.push_back(c);

        dHandVal = countHand(dHand);
    }

    if (dHandVal > 21) {

        pCurrency = pCurrency + currentBet;
        currentBet = 0;

        return PLAYER_WIN;
    }
    else if (pHandVal == dHandVal) {

        currentBet = 0;

        return PUSH_DRAW;
    }
    else if (pHandVal > dHandVal) {

        pCurrency = pCurrency + currentBet;
        currentBet = 0;

        return PLAYER_WIN;
    }

    pCurrency = pCurrency - currentBet;
    currentBet = 0;

    return DEALER_WIN;
}


    /***** Main Runtime Functions *****/

// Initialize game to be ready for first turn.
int GameProperties::init() {

    currentBet = 0;
    pCurrency = 500;
    pHandVal = 0;
    dHandVal = 0;
    dHandTrueVal = 0;


    // Get player input to set up the game
    isRunning = screen.runTitleScreen();
    
    return isRunning;
}

// Main game loop processing turns and the mediator of i/o.
int GameProperties::run() {

    Card c;
    int choice = 0, roundWinner = 0;

    while (isRunning){
        
        startNewRound();
        choice = 0;
        roundWinner = 0;

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

        pHandVal = countHand(pHand);
        dHandVal = countHand(dHand);
        // dHandTrueVal = countHand(dHand, true);  // Added in case we want to implement dealer checking

        while (pHandVal < 21 && choice != STAND) {

            choice = screen.runGameDisplay(currentBet, pHandVal, dHandVal, pHand, dHand);

            if (choice == HIT) {

                c = deck.draw();
                c.flip();
                pHand.push_back(c);
            }
            else if (choice == DOUBLE_DOWN) {

                // If not enough currency, use whats left
                if ((pCurrency - currentBet) < (currentBet * 2)) {

                    currentBet = currentBet + (pCurrency - currentBet);
                }
                else {

                    currentBet = currentBet * 2;
                }

                c = deck.draw();
                c.flip();
                pHand.push_back(c);

                choice = STAND;
            }

            pHandVal = countHand(pHand);
        }

        roundWinner = endRound();

        isRunning = screen.runEndRoundScreen(pCurrency, roundWinner, pHandVal, dHandVal, pHand, dHand);
    }

    return 1;
}

// Clean any required memory and end the game.
int GameProperties::shutdown() {

    screen.runExitScreen();

    return 1;
}
