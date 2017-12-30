/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.cpp

Class: RenderSystem

Description: A system responsable for rendering renderable objects to the screen.
*/


#include "Core.h"

#include "IRenderable.h"
#include "RenderSystem.h"


RenderSystem::RenderSystem() {

    window = NULL;

    winTitle = "";

    winWidth = 800;
    winHeight = 600;
}

RenderSystem::~RenderSystem() {

    window->close();

    delete window;
    window = NULL;
}

void RenderSystem::initialize() {

    if (winWidth > 0 && winHeight > 0) {

        window = new sf::RenderWindow(sf::VideoMode(winWidth, winHeight), sf::String(winTitle.c_str()));

        window->setKeyRepeatEnabled(false);
    }
}

void RenderSystem::update() {

    if (window != NULL) {

        window->clear();

        for (std::list<IRenderable *>::iterator iter = renderComponents.begin();
            iter != renderComponents.end();
            iter++) {

            (*iter)->render();
        }

        window->display();
    }
}

void RenderSystem::addRenderable(IRenderable *component) {

    if (component != NULL) {

        renderComponents.push_back(component);
    }
}

void RenderSystem::removeRenderable(IRenderable *component) {
    
    if (component != NULL && renderComponents.size() > 0) {

        renderComponents.remove(component);
    }
}

sf::RenderWindow *RenderSystem::getWindow() {

    return window;
}
