/*
File: main.cpp

Student: James Brooks
Assignment: Graphics and Animation Exercise 2

Description: Main file initiates the program and acts as the main draw loop.
*/


#include <list>
#include <glm\glm.hpp>

#include "VectorGrapher.h"


int main(int argc, char *argv[]) {

    // Vectors from assignment sheet
    glm::vec2 v1(0.8f, -0.2f);
    glm::vec2 v2(0.4f, 0.6f);
    glm::vec2 v3(-20.0f, 90.0f);
    
    std::list<glm::vec2> vecs;

    vecs.push_back(v1);
    vecs.push_back(v2);
    vecs.push_back(v3);

    VectorGrapher vg(vecs);

    // Success, loop drawing a nice scene
    if (vg.getInitSuccess()) {

        while (vg.isRunning()) {

            vg.draw();
            vg.update();
        }
    }

    return 0;
}