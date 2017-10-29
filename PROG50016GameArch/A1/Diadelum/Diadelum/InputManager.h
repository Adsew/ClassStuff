#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: InputManager.h

Class: InputManager

Description:
*/


class InputManager {

public:

    /***** Functions *****/

    InputManager();

    ~InputManager();

    // Initialize input manager to a usable state
    void intialize();

    // Cycle update for input manager
    void update();

    // Display relavent metrics to screen
    void display();
};

#endif
