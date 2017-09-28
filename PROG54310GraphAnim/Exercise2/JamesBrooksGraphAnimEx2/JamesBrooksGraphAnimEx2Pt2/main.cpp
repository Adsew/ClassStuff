/*
File: main.cpp

Student: James Brooks
Assignment: Graphics and Animation Exercise 2

Description: Main file initiates the program and acts as the main draw loop.
*/


#include <vector>
#include <glm\glm.hpp>

#include "VectorGrapher.h"


int main(int argc, char *argv[]) {

    VectorGrapher vg;

    // Success, loop drawing a nice scene
    if (vg.getInitSuccess()) {

        while (vg.isRunning()) {

            vg.draw();
            vg.update();
        }
    }

    return 0;
}