/*
File: Camera.cpp

Student: James Brooks

Class: Camera

Description: Handles the model view projection matrix to be applied
to all vertices in the scene. Allows simple interaction to move
the camera through the scene
*/


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Camera.h"


Camera::Camera():
    camPos(0.0f, 0.0f, 0.0f),
    camTarg(0.0f, 0.0f, 1.0f),
    upVec(0.0f, 1.0f, 0.0f) {

    view = glm::lookAt(

        camPos,
        camTarg,
        upVec
    );

    projection = glm::perspective(
        glm::radians(70.0f),
        4.0f / 3.0f,
        0.1f,
        100.0f
    );

    model = glm::mat4(1.0f);

    modified = true;
}

void Camera::updatePosition(glm::vec3 position) {

    camPos = position;

    view = glm::lookAt(

        camPos,
        camTarg,
        upVec
    );

    modified = true;
}

void Camera::updateTarget(glm::vec3 target) {

    camTarg = target;

    view = glm::lookAt(

        camPos,
        camTarg,
        upVec
    );

    modified = true;
}

void Camera::updateUpVector(glm::vec3 up) {

    upVec = up;

    view = glm::lookAt(

        camPos,
        camTarg,
        upVec
    );

    modified = true;
}

void Camera::updateFOV(float fov) {

    if (fov > 0.0f) {

        projection = glm::perspective(
            glm::radians(fov),
            4.0f / 3.0f,
            0.1f,
            100.0f
        );

        modified = true;
    }
}

void Camera::updateModelScale(float scale) {

    if (scale > 0.0f) {

        model = glm::mat4(scale);

        modified = true;
    }
}

glm::vec3 Camera::getPosition() {

    return camPos;
}

glm::vec3 Camera::getTarget() {

    return camTarg;
}

glm::vec3 Camera::getUpVector() {

    return upVec;
}

/* Set up the camera for rendering. */
/* Call before rendering any models */
void Camera::setCamera(Shader &shader) {

    if (modified) {

        mvp = projection * view * model;

        shader.setCameraAttribute(mvp, camPos);

        modified = false;
    }
}
