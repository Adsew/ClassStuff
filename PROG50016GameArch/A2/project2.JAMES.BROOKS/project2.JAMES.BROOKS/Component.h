#ifndef COMPONENT_H
#define COMPONENT_H

/*
Student: James Brooks
Class: Game Architecture

File: Component.h

Class: Component

Description: A base class for all components that can be added to a game object.
*/


#include "ComponentManager.h"
#include "Object.h"


class Component : public Object {

    friend class ComponentManager;

    /***** Variables *****/

private:

    std::string name;

    
    /***** Functions *****/

protected:
	
    Component(unsigned int uniqueID);

    Component(unsigned int uniqueID, const char *compName);

    Component(unsigned int uniqueID, const std::string &compName);

    virtual ~Component();

public:

    // Initialize the component to a usable state
    virtual void initialize() = 0;

    // Cycle update for a component
    virtual void update() = 0;

        /* Gets/Sets */

    std::string &getName();
};

#endif // !COMPONENT_H
