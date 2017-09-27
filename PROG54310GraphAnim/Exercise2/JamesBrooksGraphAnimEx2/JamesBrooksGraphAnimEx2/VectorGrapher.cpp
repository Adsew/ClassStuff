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

VectorGrapher::VectorGrapher(std::list<glm::vec2> &vectorsToDraw) {

    // Initialise GLFW
    if (glfwInit()) {

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        // Open a window and create its OpenGL context (Nick's comment)
        window = glfwCreateWindow(1024, 768, "James Brooks' Power of a Star", NULL, NULL);

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
    glDeleteProgram(progID);

    glfwDestroyWindow(window);

    glfwTerminate();
}

    /* Support Functions */

/* Load shader files and initialize openGL shader data */
void VectorGrapher::loadShaderData() {

    std::string vertexShaderLoc = "VertexShader.shader";
    std::string fragShaderLoc = "FragmentShader.shader";
    
    GLint result = GL_FALSE;
    int infoLogLen = 0;

    // Create the shaders
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile Vertex Shader
    ShaderLoader vertLoader(vertexShaderLoc);
    char const *vertSourcePointer = vertLoader.getText().c_str();
    glShaderSource(vertShaderID, 1, &vertSourcePointer, NULL);
    glCompileShader(vertShaderID);

    // Check Vertex Shader
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {

        GLchar *vertShaderErrMsg = new GLchar[infoLogLen + 1];
        glGetShaderInfoLog(vertShaderID, infoLogLen, NULL, &vertShaderErrMsg[0]);
        std::cerr << &vertShaderErrMsg[0] << "\n";
        delete vertShaderErrMsg;
    }

    // Compile Fragment Shader
    ShaderLoader fragLoader(fragShaderLoc);
    char const * fragSourcePointer = fragLoader.getText().c_str();
    glShaderSource(fragShaderID, 1, &fragSourcePointer, NULL);
    glCompileShader(fragShaderID);

    // Check Fragment Shader
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {

        GLchar *fragShaderErrMsg = new GLchar[infoLogLen + 1];
        glGetShaderInfoLog(fragShaderID, infoLogLen, NULL, &fragShaderErrMsg[0]);
        std::cerr << &fragShaderErrMsg[0] << "\n";
        delete fragShaderErrMsg;
    }

    // Link the program
    std::cout << "Linking program\n";

    progID = glCreateProgram();

    glAttachShader(progID, vertShaderID);
    glAttachShader(progID, fragShaderID);
    glLinkProgram(progID);

    // Check the program
    glGetProgramiv(progID, GL_LINK_STATUS, &result);
    glGetProgramiv(progID, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {

        GLchar *progErrMsg = new GLchar[infoLogLen + 1];
        glGetProgramInfoLog(progID, infoLogLen, NULL, &progErrMsg[0]);
        std::cerr << &progErrMsg[0] << "\n";
        delete progErrMsg;
    }


    glDetachShader(progID, vertShaderID);
    glDetachShader(progID, fragShaderID);

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);

    // Enable alpha values
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Get a handle for our buffers
    vertexPos_modelSpaceID = glGetAttribLocation(progID, "vertexPosition_modelspace");
    colourPos_vec4ID = glGetAttribLocation(progID, "colour");
}

/* Load buffer data from vectors */
void VectorGrapher::loadBufferData() {


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


}