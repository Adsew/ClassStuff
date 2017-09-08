/*
File: BlackJackIO.cpp

class: BlackjackIO

Description: Code file for all the functions that handle the "view" of the game
while it is running. These functions will to the formating and communication
with the player.
*/


#include <iostream>

#include "BlackJackIO.h"
#include "GameProperties.h"


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

// Display cards nicely in display array
// This is lengthy but mainly just for fancy display
void BlackjackIO::displayHands(vector<Card> ph, vector<Card> dh) {

    int i = 0;

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

    // Display dealer hand
    display[0] = "Dealer's Hand";

    // Build each card based on its properties
    for (i = 0; i < dh.size(); i++) {

        display[1] = display[1] + " ----";

        // Display only flipped cards of the dealer
        if (dh[i].getFlipped()) {

            // Number section
            display[2] = display[2] + " |";

            if (dh[i].getNumber() == 1) {

                display[2] = display[2] + " A|";
            }
            else if (dh[i].getNumber() < 10 && dh[i].getNumber() > 1) {

                display[2] = display[2] + " " + to_string(dh[i].getNumber()) + "|";
            }
            else if (dh[i].getNumber() == 10) {

                display[2] = display[2] + "10|";
            }
            else if (dh[i].getNumber() == 11) {

                display[2] = display[2] + " J|";
            }
            else if (dh[i].getNumber() == 12) {

                display[2] = display[2] + " Q|";
            }
            else if (dh[i].getNumber() == 13) {

                display[2] = display[2] + " K|";
            }

            // Suit section
            display[3] = display[3] + " |";

            switch (dh[i].getSuit()) {

            case heart: display[3] = display[3] + "H |"; break;

            case spade: display[3] = display[3] + "S |"; break;

            case diamond: display[3] = display[3] + "D |"; break;

            case club: display[3] = display[3] + "C |"; break;
            }
        }
        else {// Not flipped

            display[2] = display[2] + " |XX|";
            display[3] = display[3] + " |XX|";
        }

        display[4] = display[4] + " ----";
    }

    // Display player's hand
    display[5] = "Player's Hand";

    // Build each card based on its properties
    for (i = 0; i < ph.size(); i++) {

        display[6] = display[6] + " ----";

        // Number section
        display[7] = display[7] + " |";

        if (ph[i].getNumber() == 1) {

            display[7] = display[7] + " A|";
        }
        else if (ph[i].getNumber() < 10 && ph[i].getNumber() > 1) {

            display[7] = display[7] + " " + to_string(ph[i].getNumber()) + "|";
        }
        else if (ph[i].getNumber() == 10) {

            display[7] = display[7] + "10|";
        }
        else if (ph[i].getNumber() == 11) {

            display[7] = display[7] + " J|";
        }
        else if (ph[i].getNumber() == 12) {

            display[7] = display[7] + " Q|";
        }
        else if (ph[i].getNumber() == 13) {

            display[7] = display[7] + " K|";
        }

        // Suit section
        display[8] = display[8] + " |";

        switch (ph[i].getSuit()) {

        case heart: display[8] = display[8] + "H |"; break;

        case spade: display[8] = display[8] + "S |"; break;

        case diamond: display[8] = display[8] + "D |"; break;

        case club: display[8] = display[8] + "C |"; break;
        }

        display[9] = display[9] + " ----";
    }
}

// Input control game pauses until player presses enter
void BlackjackIO::enterToCont() {

    try { cin.get(); }
    catch (exception e) {}
}

// Input control to recieve a given option from player
int BlackjackIO::selectToCont(int options) {

    string input;
    int choice = 0;

    getline(cin, input);

    try {
        choice = stoi(input);
    }
    catch (exception e) {

        choice = -1;        // If garbage was entered
    }

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
int BlackjackIO::runGameDisplay(int bet, int pCount, int dCount, vector<Card> ph, vector<Card> dh) {

    int temp = 0;
    int options = 2;

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
    display[11] = "Your total: " + to_string(pCount) + "  Dealer total: " + to_string(dCount) + "  Bet: " + to_string(bet) + ".";
    display[12] = "What do you want to do?";
    display[13] = "1. Hit    2. Stand";
    display[14] = "";

    displayHands(ph, dh);

    // If player has not yet HIT, option for double available
    if (ph.size() == 2) {

        display[13] = "1. Hit    2. Stand    3. Double";
        options = 3;
    }

    pushToScreen();

    temp = selectToCont(options);

    // Ensure valid option selected, display new message
    while (temp <= 0) {

        display[14] = "Enter the number of the option you want to use.";

        pushToScreen();

        temp = selectToCont(options);
    }
    
    return temp;
}

// End round summary screen
bool BlackjackIO::runEndRoundScreen(int totCurrency, int winner,
    int pCount, int dCount, vector<Card> ph, vector<Card> dh) {

    int temp = 0;

    displayHands(ph, dh);

    display[11] = "Player: " + to_string(pCount) + "  Dealer: " + to_string(dCount) + 
        "  Player budget: " + to_string(totCurrency);
    display[12] = "";
    display[13] = "";
    display[14] = "";

    if (winner == PLAYER_WIN) {

        display[12] = "     !!!!PLAYER WINS!!!!";
    }
    else if (winner == DEALER_WIN) {

        display[12] = "    !! !!DEALER WINS!!!!";
    }
    else if (winner == PUSH_DRAW) {

        display[12] = "        !!!!PUSH!!!!";
    }

    if (totCurrency <= 0) {

        display[13] = "You're out of money! Press enter to end the game...";

        pushToScreen();

        enterToCont();

        return false;
    }

    display[13] = "Play another round?    1. Yes   2. No";

    pushToScreen();

    temp = selectToCont(2);

    while (temp < 1) {

        display[14] = "Enter 1 or 2 to select.";

        pushToScreen();

        temp = selectToCont(2);
    }

    if (temp == 1) {

        return true;
    }

    return false;
}

// Display the exit screen
void BlackjackIO::runExitScreen() {

    clearDisplay();

    display[0] = "         !!! GOOD BYE !!!";
    display[1] = "";
    display[2] = "-------  -------  -------  -------";
    display[3] = "|A    |  |A    |  |A    |  |A    |";
    display[4] = "|  H  |  |  S  |  |  D  |  |  C  |";
    display[5] = "|    A|  |    A|  |    A|  |    A|";
    display[6] = "-------  -------  -------  -------";
    display[7] = "";
    display[8] = "";
    display[9] = "";
    display[10] = "            BLACKJACK";
    display[11] = "";
    display[12] = "";
    display[13] = "       Press enter to exit.";
    display[14] = "";

    pushToScreen();

    enterToCont();
}
