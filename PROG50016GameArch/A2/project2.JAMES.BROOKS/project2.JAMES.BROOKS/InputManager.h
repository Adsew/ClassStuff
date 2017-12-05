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

public:
	
    inline static InputManager& Instance() {

		static InputManager instance;
		return instance;
	}

protected:
	
    void initialize() override;
	
    void update(float _deltaTime) override;

private:
	
    InputManager() = default;
	
    ~InputManager() = default;
	
    InputManager(const InputManager& other) = default;
};

#endif // !INPUT_MANAGER_H
