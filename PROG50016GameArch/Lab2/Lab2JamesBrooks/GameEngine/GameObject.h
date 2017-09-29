#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObject.h

Class: GameObject

Description: A game object to be used to represent objects within the game world.
*/


#include <string>
#include <list>

#include "Component.h"


class GameObject {

private:

    /***** Variables *****/

    std::list<Component *> components;

    std::string name;


public:

    /***** Functions *****/

    GameObject();

    GameObject(std::string n);

    ~GameObject();

    // Get name of the game object
    std::string getName();

    // Add component to this game object
    void addComponent(Component *comp);

    // Remove a component, if exists, from game object
   void removeComponent(Component *comp);

   // Cycle update for game object
   void update();

   // Display game object to screen
   void display();
};

#endif
