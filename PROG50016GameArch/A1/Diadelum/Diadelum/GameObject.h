#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObject.h

Class: GameObject

Description: A game object to be used to represent objects within the game world.
*/


#include <map>

#include "Object.h"


//class Component;


class GameObject : public Object {

private:

    /***** Variables *****/

    //std::map<std::string, Component *> components;

public:

    /***** Functions *****/

    GameObject();

    GameObject(std::string &n);

    virtual ~GameObject();

    // Add component to this game object
    //void addComponent(Component *comp);

    // Remove a component, if exists, from game object
    //void removeComponent(Component *comp);

    // Cycle update for game object
    virtual void update();

    // Displayer function for game object
    void display();

        // Interactivity functions

    virtual void use() = 0;

    virtual void useWith(GameObject *go) = 0;

    virtual std::string lookat() = 0;
};

#endif
