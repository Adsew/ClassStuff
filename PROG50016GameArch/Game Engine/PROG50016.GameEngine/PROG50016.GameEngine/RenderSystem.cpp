/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.cpp

Class: RenderSystem

Description: Renders data to the screen given by other classes
*/


#include <iostream>

#include "IRenderable.h"
#include "RenderSystem.h"


RenderSystem::RenderSystem() {

    
}

RenderSystem::RenderSystem(RenderSystem &rs) {}

RenderSystem::~RenderSystem() {


}

RenderSystem &RenderSystem::operator=(RenderSystem &rs) {}

int RenderSystem::priority() {

    
}

// Cycle update for render system
void RenderSystem::update() {

    
}


// Add renderable component to the list
void RenderSystem::addIRenderable(IRenderable *component) {

    if (component != NULL) {

        renderComponents.push_back(component);
    }
}

// Remove renderable component to the list
void RenderSystem::removeIRenderable(IRenderable *component) {

    std::list<IRenderable *>::iterator iter;

    for (iter = renderComponents.begin(); iter != renderComponents.end(); iter++) {

        if (component == (*iter)) {

            delete (*iter);
            iter = renderComponents.erase(iter);
            
            break;
        }
    }
}