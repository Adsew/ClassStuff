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

    Component();

    Component(int myID);

    ~Component();

    // Initialize component for use
    virtual void initialize() override;

    // Get ID for component as string
    virtual std::string getComponentId() = 0;

    // Cycle update for component
    virtual void update() = 0;
};

#endif
