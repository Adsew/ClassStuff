/*
File: BlackJack.cpp

Description: Main file creates the game and executes it.
*/


#include "GameProperties.h"


int main() {
    
    GameProperties game;

    if (game.init()) {

        game.run();
    }

    game.shutdown();

    return 0;
}

