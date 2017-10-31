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

    keyWordMap["tester"] = 10;
}

InputManager::~InputManager() {


}

// Initialize input manager to a usable state
void InputManager::intialize() {


}

// Get the text-based input's current status
std::list<std::pair<int, std::string>> InputManager::getInput() {

    return input;
}

// Cycle update for input manager
void InputManager::update() {

    std::list<std::string> tokenizedPlayerIn;
    std::string playerIn;
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
    std::string commandWord = "";

    for (std::list<std::string>::iterator majorPos = tokenizedPlayerIn.begin(); majorPos != tokenizedPlayerIn.end(); majorPos++) {

        for (std::list<std::string>::iterator subPos = majorPos; subPos != tokenizedPlayerIn.end(); subPos++) {

            // Found solo keyword
            try {

                int code = keyWordMap.at(*subPos);

                // Before pushing, push any non-keywords. Could be content like items, enviro, etc
                if (commandWord != "") {

                    input.push_back(std::pair<int, std::string>(0, commandWord));
                }

                input.push_back(std::pair<int, std::string>(code, *subPos));

                majorPos = subPos;

                break;
            }
            // Failed, so try multiword keyword
            catch (const std::out_of_range &ex) {

                commandWord += *subPos;

                try {

                    int code = keyWordMap.at(commandWord);

                    input.push_back(std::pair<int, std::string>(code, commandWord));

                    commandWord = "";

                    majorPos = subPos;

                    break;
                }
                // Wasnt either, so just keep it
                catch (const std::out_of_range &ex) {}
            }
        }
    }

    // Push any left over words as potential in scene content
    if (commandWord != "") {

        input.push_back(std::pair<int, std::string>(0, commandWord));
    }
}

// Display relavent metrics to screen
void InputManager::display() {


}
