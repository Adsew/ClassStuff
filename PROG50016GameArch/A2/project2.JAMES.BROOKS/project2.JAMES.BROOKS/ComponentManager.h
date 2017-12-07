#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: ComponentManager.h

Class: ComponentManager

Description: Maintains the memory and functionality of all components currently loaded.
*/


#include "ISystem.h"


class ComponentManager : public ISystem {

public:
    
    ComponentManager();
    
    ~ComponentManager();
};

#endif
