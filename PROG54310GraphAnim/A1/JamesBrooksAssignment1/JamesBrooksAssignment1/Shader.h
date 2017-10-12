#pragma once

/*
File: Shader.h

Student: James Brooks

Class: Shader

Description: This class will allow the addition of multiple shaders
    to create a concatinated program shader.
*/


#include <string>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Shader {

private:

    /***** Variables *****/

    GLuint programID;   // Program's ID position

    bool modified;      // True if shader added since last compile, false after compile

    std::list<GLuint> shaderList;   // List of shaders successfully added to program


public:

    /***** Functions *****/

    Shader();

    ~Shader();

    /* Should always be called to get the most up to date Program ID */
    /* A copy of program ID held by user can become out of date      */
    GLuint getProgramID();

    /* Add a shader to the shader program */
    bool addShader(std::string shaderFile, GLenum shaderType);
};

