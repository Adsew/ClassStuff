/*
File: JamesBrooksDrawScene.cpp

Student: James Brooks
Assignment: Graphics and Animation Exercise 1

Class: SceneDrawer

Description: Using various colours shaders and vertices, the class
    can be called to draw a scene to a window it creates.
*/

// NOTES FOR IDEAS: Makes a street with a lamp with light on and some randomized snow


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class SceneDrawer {

private:

    /***** Variables *****/

        /***** Internal *****/

    bool initSuccess = false;
    bool running = false;

        /***** Window *****/

    GLFWwindow* window = NULL;

        /***** Vertex / Shader *****/

    GLuint progID;
    GLuint vertexPos_modelSpaceID;
    GLuint vertexBuff;


    /***** Support Functions *****/

    int loadShader() {

        // Create and compile our GLSL program from the shaders
        GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

        // Get a handle for our buffers
        GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    }

    int loadBuffer() {

        glGenBuffers(1, &vertexBuff);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); // Can we keep changing this?
    }


public:

    /***** Constructor *****/

    SceneDrawer() {

        // Initialise GLFW
        if (glfwInit()) {

            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

            // Open a window and create its OpenGL context (Nick's comment)
            window = glfwCreateWindow(1024, 768, "James Brooks' Winter Wonderland", NULL, NULL);

            if (window != NULL) {

                glfwMakeContextCurrent(window);

                // Initialize GLEW
                if (glewInit() == GLEW_OK) {

                    // Ensure we can capture the escape key being pressed below (Nick's comment)
                    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

                    initSuccess = true;
                    running = true;
                }
                else {

                    fprintf(stderr, "Failed to initialize GLEW\n");

                    glfwTerminate();

                    loadShader();
                    loadBuffer();

                    initSuccess = false;
                }
            }
            else {

                fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");

                glfwTerminate();

                initSuccess = false;
            }
        }

        // Failed to initiate
        else {

            fprintf(stderr, "Failed to initialize GLFW\n");

            initSuccess = false;
        }
    }


    /***** Functions *****/

    bool getInitSuccess() {

        return initSuccess;
    }

    bool isRunning() {

        return running;
    }

    void update() {

        // Stop game when exit command given
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
            || glfwWindowShouldClose(window) == 1) {

            running = false;
        }
    }

    void draw() {

        // Dark blue background
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    }
};


int main(int argc, char *argv[]) {

    SceneDrawer myScene;

    // Success, loop drawing a nice scene
    if (myScene.getInitSuccess()) {

        while (myScene.isRunning()) {

            myScene.draw();
            myScene.update();
        }
    }
    
    return 0;
}