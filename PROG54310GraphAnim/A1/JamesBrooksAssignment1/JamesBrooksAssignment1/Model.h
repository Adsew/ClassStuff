#pragma once

/*
File: Model.h

Student: James Brooks

Class: Model

Description: This class can later be converted to true models which will hold 
    the vertex and colour data for the model. For now it holds my premade
    arrays for that data and renders when called.
*/


#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Model {

private:

    /***** Variables *****/

    GLuint vertexBuff;
    GLuint colourBuff;

public:

    /***** Functions *****/

    Model();
    
    ~Model();

    /* Render the stored buffer using draw arrays */
    void render(GLuint &vertexPos_modelSpaceID, GLuint &colourPos_vec4ID);
};

