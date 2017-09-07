/*
File: Card.cpp

Class: Card

Description: Class used to contain the properties of a playing card, including suit,
number, and direction facing.
*/


#include <cstdlib>
#include <ctime>

#include "Card.h"


/***** Constructor *****/

// Creates a random card. Face down by default.
Card::Card() {

    srand((unsigned)time(0));

    number = (rand() % 13) + 1;
    suit = rand() % 4;
    flipped = false;
}

// Create a specified card.
Card::Card(int num, int su) {

    number = num;
    suit = su;
    flipped = false;
}


/***** Functions *****/

// Get card number value
int Card::getNumber() {

    return number;
}

// Get card suit value
int Card::getSuit() {

    return suit;
}

// Get card flipped value
bool Card::getFlipped() {

    return flipped;
}

// Flip the card from face up to down or vice versa.
int Card::flip() {

    flipped = !flipped;

    return (int)flipped;
}

// Determine if card is a valid playing card or scrap.
bool Card::isValid() {

    if (number < 14 && number > 0 && suit < 4 && suit >= 0) {

        return true;
    }

    return false;
}
