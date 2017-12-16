#pragma once

/*
File: Model.h

Student: James Brooks

Class: Model

Description: This class can later be converted to true models which will hold 
    the vertex and colour data for the model. For now it holds my premade
    arrays for that data and renders when called.
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"


class Texture;


class Model {

private:

    /***** Variables *****/

    Texture *tex;

    GLuint vertArrObj;
    GLuint vertexBuff;
    GLuint normalBuff;
    GLuint colourBuff;

    GLfloat *vertData;
    GLfloat *normData;
    GLfloat *colData;

    int vertCount;

    // Only needed in this exercise. See constructor implementations
    // for notes. Will be removed in actual use later.
    bool needsDeletion;
    
public:
    
    /***** Functions *****/

    Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], int vCount, const char *textureLocation);

    Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], int vCount);

    Model(Shader &shader, const char *file, const char *textureLocation);

    Model(Shader &shader, const char *file);
    
    ~Model();

    /* Render the stored buffer using draw arrays */
    void render();
};

