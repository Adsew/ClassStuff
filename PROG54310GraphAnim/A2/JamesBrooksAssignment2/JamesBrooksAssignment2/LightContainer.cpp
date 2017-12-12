/*
File: LightContainer.cpp

Student: James Brooks

Class: LightContainer

Description: A container class to hold and manage any lights in a scene.
*/


#include "LightContainer.h"


LightContainer::LightContainer() {

    maxLights = 1;
}


LightContainer::~LightContainer() {

    for (unsigned int i = 0; i < lights.size(); i++) {

        delete lights[i];
    }

    lights.clear();
}

void LightContainer::setMaxLightCount(unsigned int maxNumLights) {

    maxLights = maxNumLights;
}

bool LightContainer::addLight(Light *light) {

    if (light != NULL && lights.size() < maxLights) {

        lights.push_back(light);

        return true;
    }

    return false;
}

void LightContainer::setLights(Shader &shader) {

    for (unsigned int i = 0; i < lights.size(); i++) {

        shader.setLightAttribute(lights[i], i);
    }

    shader.setLightCountAttribute(lights.size());
}
