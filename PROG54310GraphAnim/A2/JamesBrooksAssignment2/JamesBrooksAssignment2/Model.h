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

    Texture *tex1;
    Texture *tex2;

    GLuint vertArrObj;
    GLuint vertexBuff;
    GLuint normalBuff;
    GLuint colourBuff;
    GLuint textureBuff;

    GLfloat *vertData;
    GLfloat *normData;
    GLfloat *colData;
    GLfloat *texData;

    int vertCount;

    int texCount;

    // Only needed in this exercise. See constructor implementations
    // for notes. Will be removed in actual use later.
    bool needsDeletion;
    bool texNeedsDeletion;
    
public:
    
    /***** Functions *****/

    Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], GLfloat texs[], int vCount, const char *textureLocation, const char *textureLocation2);

    Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], int vCount, const char *textureLocation, const char *textureLocation2);

    Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], int vCount);

    Model(Shader &shader, const char *file, const char *textureLocation, const char *textureLocation2);

    Model(Shader &shader, const char *file);
    
    ~Model();

    /* Render the stored buffer using draw arrays */
    void render(Shader &shader);
};

