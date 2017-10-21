#pragma once

/*
File: Camera.h

Student: James Brooks

Class: Camera

Description: Handles the model view projection matrix to be applied
    to all vertices in the scene. Allows simple interaction to move
    the camera through the scene
*/


#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Camera {

private:

    /***** Variables *****/

    glm::mat4 mvp;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;

    glm::vec3 camPos;
    glm::vec3 camTarg;
    glm::vec3 upVec;

    bool modified;  // Determines whether to recalculate at draw time

public:

    /***** Functions *****/

    Camera();
    
    void updatePosition(glm::vec3 position);

    void updateTarget(glm::vec3 target);

    void updateUpVector(glm::vec3 up);

    void updateFOV(float fov);

    void updateModelScale(float scale);

    glm::vec3 getPosition();

    glm::vec3 getTarget();

    glm::vec3 getUpVector();

    /* Set up the camera for rendering. */
    /* Call before rendering any models */
    void render(GLuint &cameraPos_mat4ID);
};

