/*
File: VectorGrapher.cpp

Student: James Brooks
Assignment: Graphics and Animation Exercise 2

Class: VectorGrapher

Description: A class that acts as a renderer to create verteces out of
a given list of vectors and draw them to an OpenGL window.

Note: Lots of code is reused from my exersice 1 as it is still applicable.
*/


#include <iostream>
#include <string>

#include "ShaderLoader.h"
#include "VectorGrapher.h"


    /* Constructor/Destructor */

VectorGrapher::VectorGrapher() {

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
                loadShaderData();
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

VectorGrapher::~VectorGrapher() {

    glDeleteBuffers(1, &vertexBuff);
    glDeleteBuffers(1, &colourBuff);

    glfwDestroyWindow(window);

    glfwTerminate();
}

    /* Support Functions */

/* Load buffer data from vectors */
void VectorGrapher::loadBufferData() {
    
    int i = 0;

    glm::vec2 v1(0.8f, -0.2f);
    glm::vec2 v2(0.4f, 0.6f);
    glm::vec2 v3(-20.0f, 90.0f);
    glm::vec2 v4 = glm::normalize(v3);

    // Graph first then
    // Vectors with their arrow heads
    static const GLfloat gVertBuffData[] {

        1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,
        v1.x, v1.y, 0.0f,
        v1.x, v1.y, 0.0f,
        0.76f, -0.24f, 0.0f,
        v1.x, v1.y, 0.0f,
        0.77f, -0.14, 0.0f,

        0.0f, 0.0f, 0.0f,
        v2.x, v2.y, 0.0f,
        v2.x, v2.y, 0.0f,
        0.4f, 0.54f, 0.0f,
        v2.x, v2.y, 0.0f,
        0.35f, 0.58f, 0.0f,

        0.0f, 0.0f, 0.0f,
        v4.x, v4.y, 0.0f,
        v4.x, v4.y, 0.0f,
        -0.23f, 0.9f, 0.0f,
        v4.x, v4.y, 0.0f,
        -0.17f, 0.91f, 0.0f
    };

    // 3 vectors, 3 more for origins, 4 colour vals each
    static const GLfloat gColBuffData[] {

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f
    };

    /*for (i = 0; i < (sizeof(gVertBuffData) / sizeof(gVertBuffData[0])); i++) {

        std::cout << gVertBuffData[i] << "\n";
    }*/
    

    glGenBuffers(1, &vertexBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertBuffData), gVertBuffData, GL_STATIC_DRAW);

    glGenBuffers(1, &colourBuff);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gColBuffData), gColBuffData, GL_STATIC_DRAW);
}

/* Returns true if all openGL initialized properly and obj is usable */
bool VectorGrapher::getInitSuccess() {

    return initSuccess;
}

/* Returns true if render window has not been signaled to exit */
bool VectorGrapher::isRunning() {

    return running;
}

    /* Main Functions */

/* Basic update called in main loop */
void VectorGrapher::update() {

    // Stop game when exit command given
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
        || glfwWindowShouldClose(window) == 1) {

        running = false;
    }
}

/* Draws buffer content to screen */
void VectorGrapher::draw() {

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
        GL_FALSE,               // normalized?
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
        GL_FALSE,               // normalized?
        0,                      // stride
        (void*)0                // array buffer offset
    );

    // Begin drawing scene
    glLineWidth(5.0);
    glDrawArrays(GL_LINES, 0, 22);

    // End drawing, disable buffers
    glDisableVertexAttribArray(vertexPos_modelSpaceID);
    glDisableVertexAttribArray(colourPos_vec4ID);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}