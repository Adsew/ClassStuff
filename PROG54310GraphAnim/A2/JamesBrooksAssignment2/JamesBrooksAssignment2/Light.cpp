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
}


Light::~Light() {


}

Light Light::operator=(const Light &l) {

    colour = l.colour;
    position = l.position;
    direction = l.direction;

    ambientStrength = l.ambientStrength;
    specularStrength = l.setSpecularStrength;

    specularSize = l.specularSize;
}

// Set the colour of the light
void Light::setColour(const glm::vec3 &col) {

    colour = col;
}

// Set position of the light
void Light::setPosition(const glm::vec3 &pos) {

    position = pos;
}

// Set direction the light shines (0,0,0 for all directions)
void Light::setDirection(const glm::vec3 &dir) {

    direction = dir;
}

// Set the ambient strneght of the light
void Light::setAmbientStrength(const float &str) {

    ambientStrength = str;
}

// Set the specular strength
void Light::setSpecularStrength(const float &str) {

    specularStrength = str;
}

// Set the size of the light reflection of specular lighting
void Light::setSpecularSize(const int &size) {

    specularSize = size;
}
