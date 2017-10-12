#pragma once

/*
File: Model.h

Student: James Brooks

Class: Model

Description: A model which contains vertices and colour and can be rendered.
*/


#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Model {

private:

    /***** Variables *****/

    GLuint vaoID;

    float *vertices;
    float *colours;

public:

    /***** Functions *****/

    Model();

    ~Model();


};

