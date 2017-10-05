/*
File: Window.cpp

Student: James Brooks
Assignment: Assignment 1

Class: Window

Description: A class that acts as a renderer to create verteces out of
a given list of vectors and draw them to an OpenGL window.
*/


#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Window.h"


/* Constructor/Destructor */

Window::Window() {

    // Initialise GLFW
    if (glfwInit()) {

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        // Open a window and create its OpenGL context (Nick's comment)
        window = glfwCreateWindow(1024, 768, "James Brooks' Vector Grapher", NULL, NULL);

        if (window != NULL) {

            glfwMakeContextCurrent(window);

            // Initialize GLEW
            if (glewInit() == GLEW_OK) {

                // Ensure we can capture the escape key being pressed below (Nick's comment)
                glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

                // All good so load shader and buffer
                shader.addShader("VertexShader.shader", GL_VERTEX_SHADER);
                shader.addShader("FragmentShader.shader", GL_FRAGMENT_SHADER);

                progID = shader.getProgramID();

                // Enable alpha values
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                // Set background
                glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

                // Get a handle for our buffers
                vertexPos_modelSpaceID = glGetAttribLocation(progID, "vertexPosition_modelspace");
                colourPos_vec4ID = glGetAttribLocation(progID, "colour");

                loadBufferData();

                initSuccess = true;
                running = true;
            }
            else {

                std::cerr << "Failed to initialize GLEW\n";

                glfwTerminate();

                initSuccess = false;
            }
        }
        else {

            std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";

            glfwTerminate();

            initSuccess = false;
        }
    }

    // Failed to initiate
    else {

        std::cerr << "Failed to initialize GLFW\n";

        initSuccess = false;
    }
}

Window::~Window() {

    glDeleteBuffers(1, &vertexBuff);
    glDeleteBuffers(1, &colourBuff);

    glfwDestroyWindow(window);

    glfwTerminate();
}

/* Support Functions */

/* Load buffer data from vectors */
void Window::loadBufferData() {

    static const GLfloat gVertBuffData[]{

        // Grass using quad
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, -0.1f, 0.0f,
        -1.0f, -0.1f, 0.0f,

        // Water using quad
        -0.4f, -1.0f, 0.0f,
        0.4f, -1.0f, 0.0f,
        0.15f, -0.1f, 0.0f,
        -0.15f, -0.1f, 0.0f,

        // Sun using triangle fan
        0.5f, 0.7f, 0.0f,
        0.5f, 1.0f, 0.0f,
        0.30f, 0.8f, 0.0f,
        0.25f, 0.7f, 0.0f,
        0.30f, 0.50f, 0.0f,
        0.5f, 0.4f, 0.0f,
        0.7f, 0.50f, 0.0f,
        0.75f, 0.7f, 0.0f,
        0.7f, 0.8f, 0.0f,
        0.5f, 1.0f, 0.0f,

        // Stickman using lines
        0.6f, -0.5f, 0.0f,      // Body
        0.65f, -0.3f, 0.0f,
        0.6f, -0.5f, 0.0f,      // Left Leg
        0.55f, -0.7f, 0.0f,
        0.6f, -0.5f, 0.0f,      // Right Leg
        0.65f, -0.7f, 0.0f,
        0.645f, -0.33f, 0.0f,   // Left Arm
        0.55f, -0.23f, 0.0f,
        0.645f, -0.33f, 0.0f,   // Right Arm
        0.75f, -0.43f, 0.0f,

        // Stickman head using point
        0.67f, -0.25f, 0.0f,

        // Staff using line, hollow quad, and point
        0.5f, -0.6f, 0.0f,
        0.57f, -0.04f, 0.0f,

        0.57f, -0.04f, 0.0f,
        0.61f, 0.0f, 0.0f,
        0.58f, 0.05f, 0.0f,
        0.54f, 0.01f, 0.0f,

        0.575f, 0.005f, 0.0f,

        // Ray of light using triangle
        0.5f, 0.7f, 0.0f,
        -0.9f, -0.1f, 0.0f,
        -0.3f, -0.9f, 0.0f,

        // Wizard hat using quad strip
        0.6f, -0.15f, 0.0f,
        0.78f, -0.3f, 0.0f,
        0.67f, -0.16f, 0.0f,
        0.74f, -0.22f, 0.0f,
        0.72f, -0.13f, 0.0f,
        0.76f, -0.12f, 0.0f,
        0.8f, -0.16f, 0.0f,
        0.8f, -0.16f, 0.0f,

        // Monster using polygon and quads
        -0.8f, -0.8f, 0.0f,         // Left leg
        -0.7f, -0.8f, 0.0f,
        -0.65f, -0.5f, 0.0f,
        -0.68f, -0.5f, 0.0f,

        -0.6f, -0.8f, 0.0f,         // Right leg
        -0.5f, -0.8f, 0.0f,
        -0.61f, -0.5f, 0.0f,
        -0.65f, -0.5f, 0.0f,

        -0.68f, -0.5f, 0.0f,        // Body
        -0.61f, -0.5f, 0.0f,
        -0.55f, -0.3f, 0.0f,
        -0.61f, -0.2f, 0.0f,
        -0.68f, -0.2f, 0.0f,
        -0.74f, -0.3f, 0.0f,

        -0.55f, -0.3f, 0.0f,        // Arm
        -0.61f, -0.25f, 0.0f,
        -0.35f, -0.1f, 0.0f,
        -0.3f, -0.15f, 0.0f,
        -0.35f, -0.2f, 0.0f,

        // Monster eyes using triangles
        -0.66f, -0.3f, 0.0f,
        -0.69f, -0.28f, 0.0f,
        -0.67f, -0.26f, 0.0f,

        -0.63f, -0.3f, 0.0f,
        -0.6f, -0.28f, 0.0f,
        -0.62f, -0.26f, 0.0f,

        // Monster mouth using point
        -0.645f, -0.35f, 0.0f
    };

    static const GLfloat gColBuffData[]{

        // Grass
        0.10f, 0.55f, 0.13f, 1.0f,
        0.10f, 0.55f, 0.13f, 1.0f,
        0.12f, 0.66f, 0.15f, 1.0f,
        0.12f, 0.66f, 0.15f, 1.0f,

        // Water
        0.1f, 0.3f, 0.3f, 1.0f,
        0.1f, 0.3f, 0.3f, 1.0f,
        0.1f, 0.6f, 0.6f, 1.0f,
        0.1f, 0.6f, 0.6f, 1.0f,

        // Sun
        1.0f, 1.0f, 0.33f, 1.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,

        // Stickman
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,

        // Staff
        0.447f, 0.24f, 0.0f, 1.0f,
        0.3f, 0.3f, 0.3f, 1.0f,

        0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.5f, 0.2f,

        // Ray of light
        1.0f, 1.0f, 0.33f, 1.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        0.12f, 0.66f, 0.15f, 0.0f,

        // Wizard hat
        0.4f, 0.8f, 0.8f, 1.0f,
        0.4f, 0.8f, 0.8f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,
        0.4f, 0.8f, 0.8f, 1.0f,
        0.4f, 0.8f, 0.8f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,

        // Monster
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.5f,
        1.0f, 1.0f, 1.0f, 0.5f,
        1.0f, 1.0f, 1.0f, 0.5f,

        // Monster eyes
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        // Monster mouth
        0.7f, 0.0f, 0.0f, 1.0f
    };

    glGenBuffers(1, &vertexBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertBuffData), gVertBuffData, GL_STATIC_DRAW);

    glGenBuffers(1, &colourBuff);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gColBuffData), gColBuffData, GL_STATIC_DRAW);
}

/* Returns true if all openGL initialized properly and obj is usable */
bool Window::getInitSuccess() {

    return initSuccess;
}

/* Returns true if render window has not been signaled to exit */
bool Window::isRunning() {

    return running;
}

/* Main Functions */

/* Basic update called in main loop */
void Window::update() {

    // Stop game when exit command given
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
        || glfwWindowShouldClose(window) == 1) {

        running = false;
    }
}

/* Draws buffer content to screen */
void Window::draw() {

    // Clear buffer for further drawing
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(progID);

    // Vertices buffer
    glEnableVertexAttribArray(vertexPos_modelSpaceID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glVertexAttribPointer(
        vertexPos_modelSpaceID, // The attribute we want to configure
        3,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized
        0,                      // stride
        (void*)0                // array buffer offset
    );


    // Colour buffer
    glEnableVertexAttribArray(colourPos_vec4ID);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glVertexAttribPointer(
        colourPos_vec4ID,       // The attribute we want to configure
        4,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized
        0,                      // stride
        (void*)0                // array buffer offset
    );

    // Begin drawing scene
    glDrawArrays(GL_QUADS, 0, 4);           // Drawing grass

    glDrawArrays(GL_QUADS, 4, 4);           // Drawing water

    glDrawArrays(GL_TRIANGLE_FAN, 8, 10);   // Drawing sun

    glLineWidth(6.0);
    glDrawArrays(GL_LINES, 18, 10);         // Drawing stickman

    glPointSize(50.0);
    glDrawArrays(GL_POINTS, 28, 1);         // Drawing stickman Head

    glDrawArrays(GL_LINES, 29, 2);          // Drawing Staff

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_QUADS, 31, 4);          // Drawing staff fixture
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_POINTS, 35, 1);         // Drawing staff power

    glDrawArrays(GL_TRIANGLES, 36, 3);      // Drawing ray of light

    glDrawArrays(GL_QUAD_STRIP, 39, 8);     // Drawing wizard hat

    glDrawArrays(GL_QUADS, 47, 4);          // Drawing monster left leg
    glDrawArrays(GL_QUADS, 51, 4);          // Drawing monster right leg
    glDrawArrays(GL_POLYGON, 55, 6);        // Drawing monster body
    glDrawArrays(GL_POLYGON, 61, 5);        // Drawing monster Arm

    glDrawArrays(GL_TRIANGLES, 66, 6);      // Drawing monster eyes

    glPointSize(15.0);
    glDrawArrays(GL_POINTS, 72, 1);         // Drawing monster mouth


    // Camera view
    glm::vec3 camPos(0.0f, 0.0f, 0.0f);
    glm::vec3 camTarg(0.0f, 0.0f, 1.0f);
    glm::vec3 upVec(0.0f, 0.1f, 0.0f);

    glm::mat4 cameraMatrix = glm::lookAt(

        camPos, camTarg, upVec
    );

    /*glm::mat4 projection = glm::perspective(
        glm::
    )*/

    // End drawing, disable buffers
    glDisableVertexAttribArray(vertexPos_modelSpaceID);
    glDisableVertexAttribArray(colourPos_vec4ID);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}
