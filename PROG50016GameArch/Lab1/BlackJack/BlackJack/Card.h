#pragma once

/*
File: Card.h

Class: Card

Description: Class used to contain the properties of a playing card, including suit,
    number, and direction facing.
*/


/***** Definitions *****/


/* Directions */
#define faceDown false
#define faceUp true

/* Suits */
#define hearts 0
#define spade 1
#define diamond 2
#define club 3


class Card {

private:

    /***** Variables *****/

    int number;
    int suit;
    bool flipped;

public:

    /***** Functions *****/

    Card();                 // Creates a random card. Face down by default.

    Card(int num, int su);  // Create a specified card.

    int flip();             // Flip the card from face up to down or vice versa.

    bool isValid();         // Determine if card is a valid playing card or scrap.
};