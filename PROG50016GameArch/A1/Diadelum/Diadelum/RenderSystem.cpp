/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.cpp

Class: RenderSystem

Description: Renders data to the screen given by other classes
*/


#include <iostream>
#include <string>

#include "IRenderable.h"
#include "RenderSystem.h"


RenderSystem::RenderSystem() {}

RenderSystem::RenderSystem(RenderSystem &rs) {}

RenderSystem::~RenderSystem() {}

RenderSystem &RenderSystem::operator=(RenderSystem &rs) { return rs; }

int RenderSystem::priority() {

    return 0;
}

// Initialize the system to a usable state
void RenderSystem::initialize() {

    // Clear screen

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
        << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
        << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

// Cycle update for render system
void RenderSystem::update() {

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    for (std::list<IRenderable *>::iterator iter = renderComponents.begin(); iter != renderComponents.end(); iter++) {

        std::cout << (*iter)->render() << "\n";
    }
}

// Add renderable component to the list
void RenderSystem::addIRenderable(IRenderable *renderable) {

    if (renderable != NULL) {

        renderComponents.push_back(renderable);
    }
}

// Remove renderable component to the list
void RenderSystem::removeIRenderable(IRenderable *renderable) {

    for (std::list<IRenderable *>::iterator iter = renderComponents.begin(); iter != renderComponents.end(); iter++) {

        if (renderable == (*iter)) {

            iter = renderComponents.erase(iter);
            
            break;
        }
    }
}
