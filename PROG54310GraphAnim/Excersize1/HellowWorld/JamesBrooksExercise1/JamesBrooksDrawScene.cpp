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
#include <vector>

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
    GLuint colourPos_vec4ID;
    GLuint colourBuff;

        /***** Shader Strings *****/

    // Credit: These are the strings of shader files provided by Nick Sajadi.
    std::string vertShaderCode = ""
        "#version 120\n"
        "attribute vec3 vertexPosition_modelspace;\n"

        "uniform in vec4 colour;"
        "varying out vec4 fragColour;"

        "void main() {\n"
        "    gl_Position = vec4(vertexPosition_modelspace, 1.0);\n"
        "    fragColour = colour;"
        "}\n";

    // Frag has been modified to allow additional colours
    std::string fragShaderCode = ""
        "#version 120\n"

        "in vec4 fragColour;"

        "void main() {\n"
        
        "    gl_FragColor = fragColour;\n"
        "}\n";


    /***** Support Functions *****/

    // Credit: Majority of code is from Nick Sajadi's LoadShaders given in his example
    // I have retyped it into my own code to learn the process of making shaders
    void loadShader() {

        GLint result = GL_FALSE;
        int infoLogLen = 0;
        
        // Create the shaders
        GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Compile Vertex Shader
        char const *vertSourcePointer = vertShaderCode.c_str();
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
        char const * fragSourcePointer = fragShaderCode.c_str();
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
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

        // Get a handle for our buffers
        vertexPos_modelSpaceID = glGetAttribLocation(progID, "vertexPosition_modelspace");
        colourPos_vec4ID = glGetAttribLocation(progID, "colour");
    }

    // Creates the default buffers
    void loadBuffer() {

        // VERTICES
        static const GLfloat gVertBuffData[] = {

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

            // Staff using line and hollow quad and point
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
            0.75f, -0.23f, 0.0f,

            // Dancing monster using polygon
        };
        
        glGenBuffers(1, &vertexBuff);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gVertBuffData), gVertBuffData, GL_STATIC_DRAW);


        // COLOURS
        static const GLfloat gColBuffData[] = {
            
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
            0.3f, 0.7f, 0.7f, 1.0f,
            0.3f, 0.7f, 0.7f, 1.0f,
            0.3f, 0.7f, 0.7f, 1.0f,
            0.3f, 0.7f, 0.7f, 1.0f,

            // Dancing Monster
        };
        glGenBuffers(1, &colourBuff);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gColBuffData), gColBuffData, GL_STATIC_DRAW);
    }

public:

    /***** Constructor *****/

    // Initializes the window and buffers and shaders ready for use
    SceneDrawer() {

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
                    loadShader();
                    loadBuffer();

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


    /***** Functions *****/

    bool getInitSuccess() {

        return initSuccess;
    }

    bool isRunning() {

        return running;
    }

    // Check that the window should close
    void update() {

        // Stop game when exit command given
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
            || glfwWindowShouldClose(window) == 1) {

            running = false;
        }
    }

    // A repeatedly callable function that draws the current vertex buffer
    void draw() {

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

        glDrawArrays(GL_QUAD_STRIP, 39, 4);     // Drawing wizard hat

        // End drawing, disable buffers
        glDisableVertexAttribArray(vertexPos_modelSpaceID);
        glDisableVertexAttribArray(colourPos_vec4ID);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ~SceneDrawer() {

        glDeleteBuffers(1, &vertexBuff);
        glDeleteProgram(progID);

        glfwDestroyWindow(window);

        glfwTerminate();
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