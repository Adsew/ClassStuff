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

        while (win.isRunning()) {

            win.draw();
            win.update();
        }
    }

    return 0;
}