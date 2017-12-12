#pragma once

/*
File: LightContainer.h

Student: James Brooks

Class: LightContainer

Description: A container class to hold and manage any lights in a scene.
    Takes memory responsability for lights it holds.
*/


#include <vector>

#include "Light.h"
#include "Shader.h"


class LightContainer {

private:

    std::vector<Light *> lights;

    unsigned int maxLights;

public:

    LightContainer();

    ~LightContainer();

    void setMaxLightCount(unsigned int maxNumLights);

    bool addLight(Light *light);

    void setLights(Shader &shader);
};

