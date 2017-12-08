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


class Component;


class ComponentManager : public ISystem {

    friend class GameEngine;


    /***** Variables *****/

private:

    std::list<Component *> components;

    std::map<std::string, Component *(unsigned int uniqueID)> createComponent;

    /***** Functions *****/

private:

    ComponentManager() = default;

    ~ComponentManager();

    ComponentManager(const ComponentManager &cm) = default;

protected:

    virtual void initialize() override;

    virtual void update() override;

    template <class T>
    Component *createComponentOfType(unsigned int uniqueID);

public:

    inline static ComponentManager &Instance() {

        static ComponentManager instance;

        return instance;
    }

    template <class T>
    void addComponentType(const char *name);
};

#endif
