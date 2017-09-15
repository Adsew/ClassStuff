/*
File: JamesBrooksDrawScene.cpp

Student: James Brooks
Assignment: Graphics and Animation Exercise 1

Class: SceneDrawer

Description: Using various colours shaders and vertices, the class
    can be called to draw a scene to a window it creates.

PLEASE NOTE: This file does not require the shader.cpp or the fragment
    and vertex shader files to run the program.
    A lot of these items would normally be divided into different
    files, such as one for the class and others for each of the shader
    strings. This is due to the one cpp file requirement for submission.
    I hope this is okay and will not be an issue in the future.
*/

// NOTES FOR IDEAS: Makes a street with a lamp with light on and some randomized snow


#include <iostream>
#include <string>

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

        /***** Shader Strings *****/

    // Credit: These are the strings of shader files provided by Nick Sajadi.
    std::string vertexShader = ""
        "#version 120\n"
        "attribute vec3 vertexPosition_modelspace;\n"

        "void main() {\n"
        "    gl_Position = vec4(vertexPosition_modelspace, 1.0);\n"
        "}\n";

    std::string fragShader = ""
        "#version 120\n"

        "void main() {\n"
        // Output color = red 
        "    gl_FragColor = vec4(1, 0.5, 0.5, 1);\n"
        "}\n";


    /***** Support Functions *****/

    void loadShader() {

        // Create and compile our GLSL program from the shaders
        //progID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Get a handle for our buffers
        vertexPos_modelSpaceID = glGetAttribLocation(progID, "vertexPosition_modelspace");
    }

    void loadBuffer() {

        static const GLfloat gVertBuffData[] = {
            -0.1f, -1.0f, 0.0f,
            0.0f, -0.8f, 0.0f,
            0.1f, -1.0f, 0.0f,

            0.0f, 0.8f, 0.0f,
            -0.1f, 1.0f, 0.0f,
            0.1f, 1.0f, 0.0f

            - 0.6f, 0.5f,
            0.8f, 0.5f,
            -1.0f, 0.0f,
            1.0f, 0.0f
        };
        
        glGenBuffers(1, &vertexBuff);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gVertBuffData), gVertBuffData, GL_STATIC_DRAW);
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

        glClear(GL_COLOR_BUFFER_BIT);

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