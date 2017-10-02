#ifndef COMPONENT_H
#define COMPONENT_H

/*
Student: James Brooks
Class: Game Architecture

File: Component.h

Class: Component

Description:
*/


#include <string>

#include "Object.h"


class Component : public Object {

private:

    /***** Variables *****/

    int id;


public:

    /*****Functions *****/

    Component(int myID);

    ~Component();

    // Initialize component for use
    void initialize();

    // Get ID for component as string
    int getComponentId();

    // Cycle update for component
    void update();

    // Display component to screen
    void display();
};

#endif
