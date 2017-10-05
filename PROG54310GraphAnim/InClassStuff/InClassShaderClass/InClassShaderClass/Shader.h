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

    GLuint programID;

    std::list<GLuint> shaderList;


public:

    /***** Functions *****/

    Shader();

    ~Shader();

    GLuint getProgramID();

    bool addShader(std::string shaderFile, GLenum shaderType);
};

