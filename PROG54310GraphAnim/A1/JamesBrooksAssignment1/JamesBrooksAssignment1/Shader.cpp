/*
File: Shader.h

Student: James Brooks

Class: Shader

Description: This class will allow the addition of multiple shaders
to create a concatinated program shader.
*/


#include <iostream>

#include "ShaderLoader.h"
#include "Shader.h"


Shader::Shader() {

    programID = 0;
    modified = false;
}


Shader::~Shader() {

    glDeleteProgram(programID);
}

/* Should always be called to get the most up to date Program ID */
/* A copy of program ID held by user can become out of date      */
GLuint Shader::getProgramID() {

    std::list<GLuint>::const_iterator iter;
    GLint result = GL_FALSE;
    int infoLogLen = 0;

    // Only link if modified
    if (modified) {

        // Link the program
        std::cout << "Linking program\n";

        programID = glCreateProgram();

        for (iter = shaderList.begin(); iter != shaderList.end(); iter++) {

            glAttachShader(programID, *iter);
        }

        glLinkProgram(programID);

        // Check the program
        glGetProgramiv(programID, GL_LINK_STATUS, &result);
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLen);

        for (iter = shaderList.begin(); iter != shaderList.end(); iter++) {

            glDetachShader(programID, *iter);
            glDeleteShader(*iter);
        }

        if (infoLogLen > 0) {

            GLchar *progErrMsg = new GLchar[infoLogLen + 1];
            glGetProgramInfoLog(programID, infoLogLen, NULL, &progErrMsg[0]);
            std::cerr << &progErrMsg[0] << "\n";
            delete progErrMsg;

            glDeleteProgram(programID);
            programID = 0;
        }

        modified = false;
    }
    
    return programID;
}

/* Add a shader to the shader program */
bool Shader::addShader(std::string shaderFile, GLenum shaderType) {

    GLint result = GL_FALSE;
    int infoLogLen = 0;

    // Create the shaders
    GLuint shaderID = glCreateShader(shaderType);

    // Compile Shader
    ShaderLoader loader(shaderFile);
    std::string shaderCode = loader.getText();
    char const *sourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, NULL);
    glCompileShader(shaderID);

    // Check Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {

        GLchar *shaderErrMsg = new GLchar[infoLogLen + 1];
        glGetShaderInfoLog(shaderID, infoLogLen, NULL, &shaderErrMsg[0]);
        std::cerr << &shaderErrMsg[0] << "\n";
        delete shaderErrMsg;
    }
    else {

        modified = true;
        shaderList.push_back(shaderID);
    }

    return true;
}
