/*
Student: James Brooks
Class: Game Architecture

File: InputManager.cpp

Class: InputManager

Description: Handles input from the user and converts it into something
    usable by the engine.
*/


#include <iostream>

#include "InputManager.h"


InputManager::InputManager() {

    
}

InputManager::~InputManager() {


}

// Initialize input manager to a usable state
void InputManager::intialize() {

    keyWordMap["moveto"] = 1;
    keyWordMap["go"] = 1;
    keyWordMap["walk"] = 1;

    keyWordMap["use"] = 2;

    keyWordMap["search"] = 3;
    keyWordMap["lookat"] = 3;
    keyWordMap["examine"] = 3;

    keyWordMap["attack"] = 4;

    keyWordMap["push"] = 5;
    keyWordMap["interactwith"] = 5;
    keyWordMap["open"] = 5;

    keyWordMap["help"] = 6;
}

// Get the text-based input's current status
std::list<std::pair<int, std::string>> InputManager::getInput() {

    return input;
}

// Cycle update for input manager
void InputManager::update() {

    std::list<std::string> tokenizedPlayerIn;
    std::string playerIn = "";
    unsigned int wordStartPos = 0;

    input.clear();

    std::cout << "Enter a string\n";
    std::getline(std::cin, playerIn);
    
    // Tokenize the input into individual words
    for (unsigned int i = 0; i < playerIn.length(); i++) {

        // Ignore repeated spaces
        if ((playerIn[i] == ' ' || playerIn[i] == '\t')
            && i == wordStartPos) {
            
            wordStartPos = i + 1;
        }
        else if ( (playerIn[i] == ' ' || playerIn[i] == '\t')
            && i > wordStartPos) {

            tokenizedPlayerIn.push_back(playerIn.substr(wordStartPos, i - wordStartPos));

            wordStartPos = i + 1;
        }
        // End of the line, get final word if any
        else if (i == (playerIn.length() - 1) && i > wordStartPos) {

            tokenizedPlayerIn.push_back(playerIn.substr(wordStartPos, i - wordStartPos + 1));
        }
    }

    // Generate a formated version of the input
    // for the engine to understand and use
    std::string multiWord = "";

    for (std::list<std::string>::iterator word = tokenizedPlayerIn.begin(); word != tokenizedPlayerIn.end(); word++) {

        // Found solo keyword
        try {

            int code = keyWordMap.at(*word);

            // Before pushing, push any non-keywords. Could be content like items, enviro, etc
            if (multiWord != "") {

                input.push_back(std::pair<int, std::string>(0, multiWord));

                multiWord = "";
            }

            input.push_back(std::pair<int, std::string>(code, *word));
        }
        // Failed, so try multiword keyword
        catch (const std::out_of_range &ex) {

            multiWord += *word;

            try {

                int code = keyWordMap.at(multiWord);

                input.push_back(std::pair<int, std::string>(code, multiWord));

                multiWord = "";
            }
            // Wasnt that either, so just keep it for now
            catch (const std::out_of_range &ex) {}
        }
    }

    // Push any left over words as potential in scene content
    if (multiWord != "") {

        try {

            int code = keyWordMap.at(multiWord);

            input.push_back(std::pair<int, std::string>(code, multiWord));
        }
        catch (const std::out_of_range &ex) {
            
            input.push_back(std::pair<int, std::string>(0, multiWord));
        }
    }

    // Final error case, didnt enter anything
    if (input.size() == 0) {

        input.push_back(std::pair<int, std::string>(10, std::string("nothing")));
    }
}

// Display relavent metrics to screen
void InputManager::display() {


}
