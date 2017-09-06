#pragma once

/*
File: Deck.h

Class: Deck

Description: A specialized stack used to mimic the nature of a deck of cards.
*/


#include <stack>

#include "Card.h"


/* Deck will act as a wrapper class, managing a stack */
class Deck {

private:

    /***** Variables *****/

    int cardsInDeck;
    std::stack<Card> deck;


    /***** Support Functions *****/

    void addFullDeck();         // Adds full 52 cards to the deck.

    void emptyDeck();           // Safely dispose of all remaining cards in deck.


public:

    /***** Functions *****/

    Deck();                     // Create standard 52 card deck.

    ~Deck();                    // Safely delete all cards in the deck.

    Card draw();               // Draw a card from the top of the deck.

    Card peek();                // Draw a card from the top of the deck without removing it.

    int addCardTop(Card c);    // Add card to top of deck.

    int shuffle();              // Randomize order of cards in deck.

    int restart();              // Return deck to original 52 cards in a randomized order.
};