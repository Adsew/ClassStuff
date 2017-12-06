#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: InputManager.h

Class: InputManager

Description: Manages and refines input received from the user for use elsewhere.
*/


#include "ISystem.h"


class InputManager : public ISystem {

friend class GameEngine;


    /***** Functions *****/

private:

    InputManager() = default;

    ~InputManager() = default;

    InputManager(const InputManager& other) = default;

protected:
	
    void initialize() override;
	
    void update() override;

public:

    inline static InputManager& Instance() {

        static InputManager instance;

        return instance;
    }

};

#endif // !INPUT_MANAGER_H
