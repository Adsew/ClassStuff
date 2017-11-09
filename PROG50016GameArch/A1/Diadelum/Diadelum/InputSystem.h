#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: InputSystem.h

Class: InputSystem

Description: Handles input from the user and converts it into something
usable by the engine. Input values are set here and accessed by
anyone who needs them.
*/


#include <list>
#include <map>
#include <string>


class InputSystem {
    friend class GameEngine;

private:

    /***** Variables *****/

    std::map<std::string, int> keyWordMap;

    std::list<std::pair<int, std::string>> input;


    /***** Functions *****/

    InputSystem();

    InputSystem(InputSystem &is);

    ~InputSystem();

    InputSystem &operator=(InputSystem &is);

protected:

    // Initialize input manager to a usable state
    void initialize();

    // Cycle update for input manager
    void update();

public:

    inline static InputSystem &Instance() {

        static InputSystem instance;

        return instance;
    }

    // Get the text-based input's current status
    std::list<std::pair<int, std::string>> getInput();
};

#endif
