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


class IRenderable;


class RenderSystem {
    friend class GameEngine;

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

    // Initialize the system to a usable state
    void initialize();

    // Cycle update for render system
    void update();

public:

    // Get instance of RenderSystem
    inline static RenderSystem &Instance() {

        static RenderSystem instance;

        return instance;
    }

    // Display and special message directly to output
    void directToOut(const char *output);

    // Add renderable component to the list
    void addIRenderable(IRenderable *renderable);

    // Remove renderable component to the list
    void removeIRenderable(IRenderable *renderable);
};

#endif
