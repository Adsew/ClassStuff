#pragma once

/*
File: Light.h

Student: James Brooks

Class: Light

Description: Creates a single light object in the scene.
*/


#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Light {

private:

    glm::vec3 position;
    glm::vec3 direction;

    glm::vec4 colour;

public:
    
    Light();
    
    ~Light();
};

