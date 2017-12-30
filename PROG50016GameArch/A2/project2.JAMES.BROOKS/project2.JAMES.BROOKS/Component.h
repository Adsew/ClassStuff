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
    friend class GameObject;

    /***** Variables *****/

protected:

    GameObject *gameObject;

public:

    const std::string type;

    
    /***** Functions *****/

protected:
	
    Component(unsigned int uniqueID, const char *compType);

    Component(unsigned int uniqueID, const std::string &compType);

    virtual ~Component();

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) = 0;

public:

    // Initialize the component to a usable state
    virtual void initialize() = 0;

    // Cycle update for a component
    virtual void update() = 0;

        /* Gets/Sets */

    GameObject * const getGameObject();
};

#endif // !COMPONENT_H
