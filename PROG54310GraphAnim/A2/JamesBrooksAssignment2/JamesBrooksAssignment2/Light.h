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

    friend class Shader;

private:

    glm::vec3 colour;
    glm::vec3 position;
    glm::vec3 direction;
    
    float ambientStrength;
    float specularStrength;

    int specularSize;

    bool modified;

public:
    
    Light();
    
    ~Light();

    Light &operator=(const Light &l);

    // Set the colour of the light
    void setColour(const glm::vec3 &col);

    // Set position of the light
    void setPosition(const glm::vec3 &pos);

    // Set direction the light shines (0,0,0 for all directions)
    void setDirection(const glm::vec3 &dir);

    // Set the ambient strneght of the light
    void setAmbientStrength(const float &str);

    // Set the specular strength
    void setSpecularStrength(const float &str);

    // Set the size of the light reflection of specular lighting
    void setSpecularSize(const int &size);

    // Check if the light has been modified since last set
    bool isModified();

    // Set that the light has been set in openGL and thus not modified anymore
    void resetModified();
};

