#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: InputManager.h

Class: InputManager

Description: Handles input from the user and converts it into something
    usable by the engine.
*/


#include <list>
#include <map>
#include <string>


class InputManager {

private:

    std::map<std::string, int> keyWordMap;

    std::list<std::pair<int, std::string>> input;

public:

    /***** Functions *****/

    InputManager();

    ~InputManager();

    // Initialize input manager to a usable state
    void intialize();

    // Get the text-based input's current status
    std::list<std::pair<int, std::string>> getInput();

    // Cycle update for input manager
    void update();

    // Display relavent metrics to screen
    void display();
};

#endif
