#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: InputManager.h

Class: InputManager

Description: Manages and refines input received from the user for use elsewhere.
*/


#include <SFML/Graphics.hpp>

#include "ISystem.h"


class InputManager : public ISystem {

friend class GameEngine;

    /***** Variables *****/

private:

    std::map<sf::Keyboard::Key, bool>keyDownState;
    std::map<sf::Keyboard::Key, bool>keyPressedState;
    std::map<sf::Keyboard::Key, bool>keyReleasedState;

    float deltaTime;

    bool gameCloseTriggered;


    /***** Functions *****/

private:

    InputManager() = default;

    ~InputManager() = default;

    InputManager(const InputManager& other) = default;

protected:
	
    virtual void initialize() override;
	
    virtual void clean() override;

    virtual void update() override;

public:

    inline static InputManager& Instance() {

        static InputManager instance;

        return instance;
    }

    // True if key was pressed during this update cycle
    bool getKeyPressed(const sf::Keyboard::Key &key);

    // True if key was released during this update cycle
    bool getKeyReleased(const sf::Keyboard::Key &key);

    // True if key is held down, false if up
    bool getKeyDown(const sf::Keyboard::Key &key);

    // Sets the game exit flag to true (should be moved elsewhere, not sure where though)
    void exit();
};

#endif // !INPUT_MANAGER_H
