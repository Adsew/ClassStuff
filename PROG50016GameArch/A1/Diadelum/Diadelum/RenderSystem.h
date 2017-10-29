#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.h

Class: RenderSystem

Description: Renders data to the screen given by other classes
*/


#include <list>

#include "ISystem.h"


class IRenderable;


class RenderSystem : public ISystem {

private:


    /***** Variables *****/

    std::list<IRenderable *> renderComponents;

private:


    /***** Functions *****/

    RenderSystem();

    RenderSystem(RenderSystem &rs);

    ~RenderSystem();

    RenderSystem &operator=(RenderSystem &rs);

protected:

    // Get item proirity to render
    int priority();

    // Cycle update for render system
    void update();

public:

    // Get instance of RenderSystem
    inline static RenderSystem &Instance() {

        static RenderSystem instance;

        return instance;
    }

    // Add renderable component to the list
    void addIRenderable(IRenderable *component);

    // Remove renderable component to the list
    void removeIRenderable(IRenderable *component);
};

#endif
