#pragma once

/*
File: Window.h

Student: James Brooks

Class: Window

Description: A class that acts as a renderer to create verteces out of
a given list of vectors and draw them to an OpenGL window.
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "ModelContainer.h"


class Window {

private:

    /***** Variables *****/

    /***** Internal *****/

    bool initSuccess = false;
    bool running = false;

    /***** Window *****/

    GLFWwindow *window = NULL;

    /***** Vertex / Shader / Camera *****/

    Shader shader;

    Camera camera;

    ModelContainer models;

public:

    /***** Functions *****/


    /* Constructor */
    Window();

    /* Destructor */
    ~Window();

    /* Sets the clear colour when window refreshes */
    void setClearColour(float r, float g, float b, float a);

    /* Returns true if all openGL initialized properly and obj is usable */
    bool getInitSuccess();

    /* Returns true if render window has not been signaled to exit */
    bool isRunning();

    /* Basic update called in main loop */
    void update();

    /* Draws buffer content to screen */
    void draw();
};

