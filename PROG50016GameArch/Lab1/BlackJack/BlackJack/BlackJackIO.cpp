/*
File: BlackJackIO.cpp

class: BlackjackIO

Description: Code file for all the functions that handle the "view" of the game
while it is running. These functions will to the formating and communication
with the player.
*/


#include <iostream>

#include "BlackJackIO.h"


/***** Constructor *****/

BlackjackIO::BlackjackIO() {

    clearDisplay();
}


/***** Functions *****/

// Whipe the display to blank strings
void BlackjackIO::clearDisplay() {

    int i = 0;

    for (i = 0; i < DISPLAY_SIZE; i++) {

        display[i] = "";
    }
}

// Push the current display to the output stream
void BlackjackIO::pushToScreen() {

    int i = 0;
    
    // Clear the console to make a fresher looking game
    for (i = 0; i < 10; i++) {

        cout << "\n";
    }

    for (i = 0; i < DISPLAY_SIZE; i++) {

        cout << display[i];
        cout << "\n";
    }
}

// Input control game pauses until player presses enter
void BlackjackIO::enterToCont() {

    cin.get();
}

// Input control to recieve a given option from player
int BlackjackIO::selectToCont(int options) {

    string input;
    int choice = 0;

    getline(cin, input);

    choice = stoi(input);

    if (choice > 0 && choice <= options) {

        return choice;
    }

    return -1;
}

// Display a title screen and ask player to begin
bool BlackjackIO::runTitleScreen() {

    display[0]  = "    !!! WELCOME TO BLACKJACK !!!";
    display[1]  = "";
    display[2]  = "-------  -------  -------  -------";
    display[3]  = "|A    |  |A    |  |A    |  |A    |";
    display[4]  = "|  H  |  |  S  |  |  D  |  |  C  |";
    display[5]  = "|    A|  |    A|  |    A|  |    A|";
    display[6]  = "-------  -------  -------  -------";
    display[7]  = "";
    display[8]  = "    (H)earts          (S)pades";
    display[9]  = "   (D)iamonds         (C)lubs";
    display[10] = "";
    display[11] = "";
    display[12] = "";
    display[13] = "       Press enter to begin!";
    display[14] = "";

    pushToScreen();

    enterToCont();
    
    clearDisplay();
    
    display[9] = "    Dealing....";

    return true;
}

// Request the current bet from the player
int BlackjackIO::runBetting(int maxBet){
    
    int input = 0;
    
    display[14] = "How much do you wish to bet? Current budget: " + to_string(maxBet);
    
    pushToScreen();

    input = selectToCont(maxBet);
    
    while (input <= 0){
        
        display[14] = "Bet must be in your budget. Current budget: " + to_string(maxBet);
        
        pushToScreen();

        input = selectToCont(maxBet);
    }

    return input;
}

// Runs the current main game display
int BlackjackIO::runGameDisplay(int bet, vector<Card> ph, vector<Card> dh) {

    int temp = 0;

    display[0] = "";
    display[1] = "";
    display[2] = "";
    display[3] = "";
    display[4] = "";
    display[5] = "";
    display[6] = "";
    display[7] = "";
    display[8] = "";
    display[9] = "";
    display[10] = "";
    display[11] = "Your bet: " + to_string(bet) + ".";
    display[12] = "What do you want to do?";
    display[13] = "1. Hit    2. Stand    3. Double";
    display[14] = "";

    pushToScreen();

    while (temp <= 0) {

        display[14] = "Enter the number of the option you want to use.";

        pushToScreen();

        temp = selectToCont(3);
    }
    
    return temp;
}

// Display the exit screen
void BlackjackIO::runExitScreen() {

    clearDisplay();

    display[0] = "";
    display[1] = "";
    display[2] = "";
    display[3] = "";
    display[4] = "";
    display[5] = "";
    display[6] = "";
    display[7] = "";
    display[8] = "";
    display[9] = "";
    display[10] = "";
    display[11] = "";
    display[12] = "";
    display[13] = "Goodbye!";
    display[14] = "";

    //pushToScreen();

    enterToCont();
}
/*
display[0] = "";
display[1] = "";
display[2] = "";
display[3] = "";
display[4] = "";
display[5] = "";
display[6] = "";
display[7] = "";
display[8] = "";
display[9] = "";
display[10] = "";
display[11] = "";
display[12] = "";
display[13] = "";
display[14] = "";
*/