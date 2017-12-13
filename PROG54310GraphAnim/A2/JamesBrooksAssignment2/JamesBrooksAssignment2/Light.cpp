/*
File: Light.cpp

Student: James Brooks

Class: Light

Description: Creates a single light object in the scene.
*/


#include "Light.h"


Light::Light()
    :
    colour(0, 0, 0),
    position(0, 0, 0),
    direction(0, 0, 0)
    {

    ambientStrength = 1.0f;
    specularStrength = 1.0f;

    specularSize = 2;

    modified = false;
}


Light::~Light() {


}

Light &Light::operator=(const Light &l) {

    colour = l.colour;
    position = l.position;
    direction = l.direction;

    ambientStrength = l.ambientStrength;
    specularStrength = l.specularStrength;

    specularSize = l.specularSize;

    modified = true;

    return *this;
}

// Set the colour of the light
void Light::setColour(const glm::vec3 &col) {

    colour = col;

    modified = true;
}

// Set position of the light
void Light::setPosition(const glm::vec3 &pos) {

    position = pos;

    modified = true;
}

// Set direction the light shines (0,0,0 for all directions)
void Light::setDirection(const glm::vec3 &dir) {

    direction = dir;

    modified = true;
}

// Set the ambient strneght of the light
void Light::setAmbientStrength(const float &str) {

    ambientStrength = str;

    modified = true;
}

// Set the specular strength
void Light::setSpecularStrength(const float &str) {

    specularStrength = str;

    modified = true;
}

// Set the size of the light reflection of specular lighting
void Light::setSpecularSize(const int &size) {

    specularSize = size;

    modified = true;
}

// Check if the light has been modified since last set
bool Light::isModified() {

    return modified;
}

// Set that the light has been set in openGL and thus not modified anymore
void Light::resetModified() {

    modified = false;
}
