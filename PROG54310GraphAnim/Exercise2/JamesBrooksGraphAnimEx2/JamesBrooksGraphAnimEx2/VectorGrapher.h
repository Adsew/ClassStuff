#pragma once

/*
File: VectorGrapher.h

Student: James Brooks
Assignment: Graphics and Animation Exercise 2

Class: VectorGrapher

Description: A class that acts as a renderer to create verteces out of
    a given list of vectors and draw them to an OpenGL window.
*/


#include <list>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class VectorGrapher {

private:

    /***** Variables *****/

        /***** Internal *****/

    bool initSuccess = false;
    bool running = false;

        /***** Window *****/

    GLFWwindow *window = NULL;

        /***** Vertex / Shader *****/

    GLuint progID;
    GLuint vertexPos_modelSpaceID;
    GLuint vertexBuff;
    GLuint colourPos_vec4ID;
    GLuint colourBuff;


    /***** Functions *****/

    /* Load shader files and initialize openGL shader data */
    void loadShaderData();

    /* Load buffer data from vectors */
    void loadBufferData();

public:

    /* Constructor */
    VectorGrapher(std::list<glm::vec2> &vectorsToDraw);

    /* Destructor */
    ~VectorGrapher();

    /* Returns true if all openGL initialized properly and obj is usable */
    bool getInitSuccess();

    /* Returns true if render window has not been signaled to exit */
    bool isRunning();

    /* Basic update called in main loop */
    void update();

    /* Draws buffer content to screen */
    void draw();
};