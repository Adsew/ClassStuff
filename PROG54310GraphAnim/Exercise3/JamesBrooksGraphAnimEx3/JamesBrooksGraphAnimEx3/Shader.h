#pragma once

/*
File: Shader.h

Student: James Brooks

Class: Shader

Description: This class will allow the addition of multiple shaders
    to create a concatinated program shader.
*/


#include <list>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Shader {

private:

    /***** Variables *****/

    GLuint programID;   // Program's ID position

    GLuint vertexPos_modelSpaceID;
    GLuint colourPos_vec4ID;
    GLuint cameraPos_mat4ID;

    bool modified;      // True if shader added since last compile, false after compile

    std::list<GLuint> shaderList;   // List of shaders successfully added to program


public:

    /***** Functions *****/

    Shader();

    ~Shader();

    /* Should always be called to get the most up to date Program ID */
    /* A copy of program ID held by user can become out of date      */
    GLuint getProgramID();

    /* Generate the handles for the currently built shader program for all types */
    void generateHandles(const char *vertexVar, const char *colourVar, const char *cameraVar);

    /* Generate the vertex handle for the currently built shader program */
    void genHandleVertex(const char *vertexVar);

    /* Generate the colour handle for the currently built shader program */
    void genHandleColour(const char *colourVar);

    /* Generate the camera handle for the currently built shader program */
    void genHandleCamera(const char *cameraVar);

    /* Sets the bound buffer to the vertex variable of the shader program */
    void setVertexAttribute();

    /* Sets the bound buffer to the colour variable of the shader program */
    void setColourAttribute();

    /* Sets the camera matrix to the camera variable of the shader program */
    void setCameraAttribute(glm::mat4 &mvp);

    /* Add a shader to the shader program */
    bool addShader(std::string shaderFile, GLenum shaderType);
};

