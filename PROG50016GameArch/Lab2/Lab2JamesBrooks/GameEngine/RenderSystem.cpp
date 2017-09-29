/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.cpp

Class: RenderSystem

Description: Renders data to the screen given by other classes
*/


#include <iostream>

#include "RenderSystem.h"


RenderSystem::RenderSystem() {

    name = "";
    width = 0;
    height = 0;
    fullscreen = true;
}

RenderSystem::~RenderSystem() {


}

// Initialize render system to a usable point
void RenderSystem::initialize(std::string n, int w, int h, bool fsMode) {

    name = n;
    width = w;
    height = h;
    fullscreen = fsMode;
}

// Cycle update for render system
void RenderSystem::update() {


}

// Display objects to screen
void RenderSystem::display() {

    std::cout << "Render System\n";
    std::cout << "------------------\n";

    std::cout << "Name: " << name << "\n";
    std::cout << "Width: " << width << " Height: " << height << "\n";

    if (fullscreen) {

        std::cout << "Fullscreen: true\n";
    }
    else {

        std::cout << "Fullscreen: false\n";
    }
}
