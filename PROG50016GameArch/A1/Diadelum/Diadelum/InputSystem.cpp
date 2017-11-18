/*
Student: James Brooks
Class: Game Architecture

File: InputSystem.cpp

Class: InputSystem

Description: Handles input from the user and converts it into something
    usable by the engine. Input values are set here and accessed by
    anyone who needs them.
*/


#include <iostream>

#include "InputCodes.h"
#include "InputSystem.h"


InputSystem::InputSystem() {}

InputSystem::InputSystem(InputSystem &is) {}

InputSystem::~InputSystem() {}

InputSystem &InputSystem::operator=(InputSystem &is) { return is; }

// Initialize input manager to a usable state
void InputSystem::initialize() {

    keyWordMap["move to"] = IN_CODE_MOVE;
    keyWordMap["go"] = IN_CODE_MOVE;
    keyWordMap["walk"] = IN_CODE_MOVE;
    keyWordMap["enter"] = IN_CODE_MOVE;

    keyWordMap["use"] = IN_CODE_USE;
    keyWordMap["push"] = IN_CODE_USE;
    keyWordMap["interact with"] = IN_CODE_USE;
    keyWordMap["open"] = IN_CODE_USE;

    keyWordMap["search"] = IN_CODE_SEARCH;
    keyWordMap["look at"] = IN_CODE_SEARCH;
    keyWordMap["examine"] = IN_CODE_SEARCH;

    keyWordMap["pickup"] = IN_CODE_PICKUP;
    keyWordMap["get"] = IN_CODE_PICKUP;

    keyWordMap["talk to"] = IN_CODE_TALK;

    keyWordMap["attack"] = IN_CODE_ATTACK;

    keyWordMap["help"] = IN_CODE_HELP;

    keyWordMap["save"] = IN_CODE_SAVE;

    keyWordMap["exit"] = IN_CODE_EXIT;

    keyWordMap["with"] = IN_CODE_CONNECT;
    keyWordMap["on"] = IN_CODE_CONNECT;
}

// Get the text-based input's current status
std::list<std::pair<int, std::string>> InputSystem::getInput() {

    return input;
}

// Cycle update for input manager
void InputSystem::update() {

    std::list<std::string> tokenizedPlayerIn;
    std::string playerIn = "";
    unsigned int wordStartPos = 0;

    input.clear();

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

                input.push_back(std::pair<int, std::string>(IN_CODE_WORDS, std::string(multiWord)));

                multiWord = "";
            }

            input.push_back(std::pair<int, std::string>(code, std::string(*word)));
        }
        // Failed, so try multiword keyword
        catch (const std::out_of_range &ex) {

            if (multiWord == "") {

                multiWord += *word;
            }
            else {

                multiWord += " " + *word;
            }

            try {

                int code = keyWordMap.at(multiWord);

                input.push_back(std::pair<int, std::string>(code, std::string(multiWord)));

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

            input.push_back(std::pair<int, std::string>(code, std::string(multiWord)));
        }
        catch (const std::out_of_range &ex) {
            
            input.push_back(std::pair<int, std::string>(IN_CODE_WORDS, std::string(multiWord)));
        }
    }

    // Final error case, didnt enter anything
    if (input.size() == 0) {

        input.push_back(std::pair<int, std::string>(IN_CODE_NOTHING, std::string("nothing")));
    }
}
