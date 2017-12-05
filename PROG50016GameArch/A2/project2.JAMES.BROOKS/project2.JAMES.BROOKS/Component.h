#ifndef COMPONENT_H
#define COMPONENT_H

/*
Student: James Brooks
Class: Game Architecture

File: Component.h

Class: Component

Description: A base class for all components that can be added to a game object.
*/


#include "Object.h"


class Component : public Object {

private:
	
    int id;

public:
	
    Component();// Look at calling base
	
    ~Component();

	virtual std::string getComponentId() = 0;
	
    virtual void initialize() override;
};

#endif // !COMPONENT_H
