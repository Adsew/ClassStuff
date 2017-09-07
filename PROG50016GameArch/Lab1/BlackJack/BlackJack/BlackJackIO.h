#pragma once

/*
File: BlackJackIO.h

class: BlackjackIO

Description: Header file for all the functions that handle the "view" of the game
    while it is running. These functions will to the formating and communication
    with the player.
*/


#include <string>
using namespace std;


#define DISPLAY_SIZE 15


class BlackjackIO {

private:

    /***** Variables *****/

    string display[DISPLAY_SIZE];


    /***** Support Functions *****/

    void clearDisplay();            // Whipe the display to blank strings

    void pushToScreen();            // Push the current display to the output stream

    void enterToCont();             // Input control game pauses until player presses enter

    int selectToCont(int options);  // Input control to recieve a given option from player

public:

    /***** User Functions *****/

    BlackjackIO();

    bool runTitleScreen();          // Display a title screen and ask player to begin

    void exitScreen();              // Display the exit screen
};
