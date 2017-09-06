/*
File: Card.cpp

Class: Card

Description: Class used to contain the properties of a playing card, including suit,
number, and direction facing.
*/


#include "Card.h"


/***** Constructor *****/

Card::Card() {

    number = RANDOM NUMBER;
    suit = RANDOM NUMBER;
    flipped = false;
}

Card::Card(int num, int su) {

    // Ensure safe values were passed
    if (num < 14 && num > 0 && su < 4 && su >= 0) {

        number = num;
        suit = su;
    }
    else {

        number = RANDOM NUMBER;
        suit = RANDOM NUMBER;
    }

    flipped = false;
}


/***** Functions *****/

int Card::flip() {

    flipped = !flipped;

    return (int)flipped;
}