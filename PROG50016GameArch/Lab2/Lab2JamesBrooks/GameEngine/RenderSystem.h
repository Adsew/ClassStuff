#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.h

Class: RenderSystem

Description: Renders data to the screen given by other classes
*/


#include <string>


class RenderSystem {

private:

    /***** Variables *****/

    std::string name;

    int width;
    int height;

    bool fullscreen;


public:

    /***** Functions *****/

    RenderSystem();

    ~RenderSystem();

    // Initialize render system to a usable point
    void initialize(std::string n, int w, int h, bool fsMode);

    // Cycle update for render system
    void update();

    // Display objects to screen
    void display();
};

#endif
