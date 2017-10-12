/*
File: main.cpp

Student: James Brooks
Assignment: Assignment 1

Description: Main file initiates the program and acts as the main draw loop.
*/


#include "Window.h"


int main(int argc, char *argv[]) {

    Window win;

    // Success, loop drawing a nice scene
    if (win.getInitSuccess()) {

        win.setClearColour(0.0f, 0.0f, 0.5f, 1.0f);

        while (win.isRunning()) {

            win.draw();
            win.update();
        }
    }

    return 0;
}