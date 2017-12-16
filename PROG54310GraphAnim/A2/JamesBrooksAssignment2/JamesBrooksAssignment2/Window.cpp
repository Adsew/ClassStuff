/*
File: Window.cpp

Student: James Brooks

Class: Window

Description: A class that acts as a renderer to create verteces out of
a given list of vectors and draw them to an OpenGL window.
*/


#include <iostream>

#include "PresetModelData.h"
#include "Window.h"


    /***** Support Functions *****/
/* Would be implemented in a game object based class in an engine */
/* Simply used for rotating camera right now and simplifying code */
/* in the update function.                                        */

void rotateCounterClockwise(glm::vec3 &vec, float r) {

    if (r <= 1.0f && r > 0.0f) {

        if (vec.z > 0.0f && vec.x >= 0.0f) {

            vec.z -= r;
            vec.x += r;
        }
        else if (vec.z >= 0.0f && vec.x < 0.0f) {

            vec.z += r;
            vec.x += r;
        }
        else if (vec.z <= 0.0f && vec.x > 0.0f) {

            vec.z -= r;
            vec.x -= r;
        }
        else if (vec.z < 0.0f && vec.x <= 0.0f) {

            vec.z += r;
            vec.x -= r;
        }
    }
}

void rotateClockwise(glm::vec3 &vec, float r) {

    if (r <= 1.0f && r > 0.0f) {

        if (vec.z >= 0.0f && vec.x > 0.0f) {

            vec.z += r;
            vec.x -= r;
        }
        else if (vec.z > 0.0f && vec.x <= 0.0f) {

            vec.z -= r;
            vec.x -= r;
        }
        else if (vec.z < 0.0f && vec.x >= 0.0f) {

            vec.z += r;
            vec.x += r;
        }
        else if (vec.z <= 0.0f && vec.x < 0.0f) {

            vec.z -= r;
            vec.x += r;
        }
    }
}

    /***** Functions *****/

/* Constructor/Destructor */

Window::Window() {

    // Initialise GLFW
    if (glfwInit()) {

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        // Open a window and create its OpenGL context (Nick's comment)
        window = glfwCreateWindow(1024, 768, "Walk Around Scene", NULL, NULL);

        if (window != NULL) {

            glfwMakeContextCurrent(window);

            // Initialize GLEW
            if (glewInit() == GLEW_OK) {

                // Ensure we can capture the escape key being pressed below (Nick's comment)
                glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

                // All good so load shader and buffer
                shader.addShader("VertexShader.shader", GL_VERTEX_SHADER);
                //shader.addShader("FragmentShader.shader", GL_FRAGMENT_SHADER);
                shader.addShader("LightingShader.shader", GL_FRAGMENT_SHADER);

                shader.use();

                shader.generateHandles("vec3_position", "vec3_normal", "vec4_colour", "mvp_camera", "vec3_cam_pos");
                shader.genHandleLights("light", "num_lights_used", 3);
                shader.genHandleTextures("objTexture1", "objTexture2", "activeTextures");

                // Set default background
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

                // Set camera defaults
                camera.updatePosition(glm::vec3(0.0f, 0.0f, 0.0f));
                camera.updateTarget(glm::vec3(0.0f, 0.0f, 1.0f));

                // Set lights in the scene
                lights.setMaxLightCount(3);     // Max is set by the array size in the fragment shader
                                                // It can not be set dynamically without extensions or buffers
                Light *tempLight = NULL;
                
                    // Main sun, forward in the scene
                tempLight = new Light();
                tempLight->setColour(glm::vec3(1.0f, 1.0f, 1.0f));
                tempLight->setPosition(glm::vec3(0.0f, 2.0f, 4.0f));
                tempLight->setAmbientStrength(0.9f);
                tempLight->setSpecularStrength(1.0f);
                tempLight->setSpecularSize(64);

                lights.addLight(tempLight);

                    // Second bright light, to the left of the scene
                tempLight = new Light();
                tempLight->setColour(glm::vec3(1.0f, 1.0f, 1.0f));
                tempLight->setPosition(glm::vec3(4.0f, 2.0f, 1.0f));
                tempLight->setAmbientStrength(0.5f);
                tempLight->setSpecularStrength(1.0f);
                tempLight->setSpecularSize(128);

                lights.addLight(tempLight);

                    // Red light emitted from the star in the center of the scene
                tempLight = new Light();
                tempLight->setColour(glm::vec3(1.0f, 0.0f, 0.0f));
                tempLight->setPosition(glm::vec3(0.5f, 0.7f, 1.0f));
                tempLight->setDirection(glm::vec3(0.0f, -1.0f, 1.0f));
                tempLight->setAmbientStrength(1.0f);
                tempLight->setSpecularStrength(0.0f);
                tempLight->setSpecularSize(32);

                lights.addLight(tempLight);

                // Load the models
                // Render order must be in order of opaque -> translucent for optimal depth testing
                models.addModel(new Model(shader, terrainVertData, terrainNormData, terrainColData, sizeof(terrainVertData) / sizeof(GLfloat) / 3));
                models.addModel(new Model(shader, "Monster.model", "fur.png"));
                models.addModel(new Model(shader, stickmanVertData, stickmanNormData, stickmanColData, sizeof(stickmanVertData) / sizeof(GLfloat) / 3));
                models.addModel(new Model(shader, wizhatVertData, wizhatNormData, wizhatColData, sizeof(wizhatVertData) / sizeof(GLfloat) / 3));
                models.addModel(new Model(shader, staffVertData, staffNormData, staffColData, sizeof(staffVertData) / sizeof(GLfloat) / 3));
                models.addModel(new Model(shader, "Raylight.model"));
                models.addModel(new Model(shader, sunVertData, sunNormData, sunColData, sizeof(sunVertData) / sizeof(GLfloat) / 3));
                
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

    glfwDestroyWindow(window);

    glfwTerminate();
}


    /* Support Functions */

/* Sets the clear colour when window refreshes */
void Window::setClearColour(float r, float g, float b, float a) {

    glClearColor(r, g, b, a);
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

    glm::vec3 pos = camera.getPosition();
    glm::vec3 targ = camera.getTarget() - pos;
    glm::vec3 right(targ.z, targ.y, -targ.x);

    // Stop game when exit command given
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
        || glfwWindowShouldClose(window) == 1) {

        running = false;
    }

    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

        pos += targ / 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

        pos -= targ / 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

        pos += right / 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

        pos -= right / 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

        pos.y += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

        pos.y -= 0.1f;
    }

    // Rotation
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

        rotateClockwise(targ, 0.05f);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {

        rotateCounterClockwise(targ, 0.05f);
    }
    
    camera.updatePosition(pos);
    camera.updateTarget(pos + targ);
}

/* Draws buffer content to screen */
void Window::draw() {

    // Clear buffer for further drawing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    camera.setCamera(shader);

    lights.setLights(shader);

    models.render();
    
    glfwSwapBuffers(window);

    glfwPollEvents();
}