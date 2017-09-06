/*
File: Deck.cpp

Class: Deck

Description: A specialized stack used to mimic the nature of a deck of cards.
*/


#include <vector>
#include <cstdlib>
#include <ctime>

#include "Deck.h"


/***** Constructor/Destructor *****/

// Create standard 52 card deck.
Deck::Deck() {

    cardsInDeck = 0;

    addFullDeck();

    shuffle();
}

// Safely delete all cards in the deck.
Deck::~Deck() {

    emptyDeck();
}


/***** Functions *****/

// Adds full 52 cards to the deck.
void Deck::addFullDeck() {

    int i = 0, j = 0;

    for (i = 0; i < 4; i++) {
        for (j = 1; j < 14; j++) {

            Card c(j, i);

            addCardTop(c);
        }
    }
}

// Safely dispose of all remaining cards in deck.
void Deck::emptyDeck() {

    while (!deck.empty()) {

        draw(); // We dont need the cards, just delete them.
    }
}

// Draw a card from the top of the deck.
Card Deck::draw() {

    Card temp;

    if (!deck.empty()) {

        cardsInDeck = cardsInDeck - 1;

        temp = deck.top();
        deck.pop();
        
        return temp;
    }
    
    return Card(-1, -1); // Return an invalid card
}

// Draw a card from the top of the deck without removing it.
Card Deck::peek() {

    if (!deck.empty()) {

        return deck.top();
    }

    return Card(-1, -1); // Return an invalid card
}

// Add card to top of deck.
int Deck::addCardTop(Card c) {

    if (c.isValid()) {

        deck.push(c);

        cardsInDeck = cardsInDeck + 1;

        return 1;
    }

    return 0;
}

// Randomize order of cards in deck.
int Deck::shuffle() {

    std::vector<Card> tempDeck;
    int i = 0;

    srand((unsigned)time(0));

    // Empty the deck into a temp location.
    while (!deck.empty()) {

        tempDeck.push_back( deck.top() );
        deck.pop();
    }

    // Add back cards to deck in a random order.
    while (!tempDeck.empty()) {

        i = rand() % tempDeck.size();

        deck.push(tempDeck[i]);

        tempDeck.erase(tempDeck.begin() + i);
    }

    return 1;
}

// Return deck to original 52 cards in a randomized order.
int Deck::restart() {

    emptyDeck();

    addFullDeck();

    shuffle();

    return 1;
}
