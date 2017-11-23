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

        // Enable alpha values
        glEnable(GL_BLEND);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);
        glClearDepth(1.0f);
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        modified = false;
    }
    
    return programID;
}

/* Generate the handles for the currently built shader program */
void Shader::generateHandles(const char *vertexVar, const char *colourVar, const char *cameraVar) {

    vertexPos_modelSpaceID = glGetAttribLocation(getProgramID(), vertexVar);
    colourPos_vec4ID = glGetAttribLocation(getProgramID(), colourVar);
    cameraPos_mat4ID = glGetUniformLocation(getProgramID(), cameraVar);
}

/* Generate the vertex handle for the currently built shader program */
void Shader::genHandleVertex(const char *vertexVar) {

    vertexPos_modelSpaceID = glGetAttribLocation(getProgramID(), vertexVar);
}

/* Generate the colour handle for the currently built shader program */
void Shader::genHandleColour(const char *colourVar) {

    colourPos_vec4ID = glGetAttribLocation(getProgramID(), colourVar);
}

/* Generate the camera handle for the currently built shader program */
void Shader::genHandleCamera(const char *cameraVar) {

    cameraPos_mat4ID = glGetUniformLocation(getProgramID(), cameraVar);
}

/* Sets the bound buffer to the vertex variable of the shader program */
void Shader::setVertexAttribute() {

    glVertexAttribPointer(
        vertexPos_modelSpaceID, // The attribute we want to configure
        3,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized
        0,                      // stride
        (void*)0                // array buffer offset
    );

    glEnableVertexAttribArray(vertexPos_modelSpaceID);
}

/* Sets the bound buffer to the colour variable of the shader program */
void Shader::setColourAttribute() {

    glVertexAttribPointer(
        colourPos_vec4ID,       // The attribute we want to configure
        4,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized
        0,                      // stride
        (void*)0                // array buffer offset
    );

    glEnableVertexAttribArray(colourPos_vec4ID);
}

/* Sets the camera matrix to the camera variable of the shader program */
void Shader::setCameraAttribute(glm::mat4 &mvp) {

    glUniformMatrix4fv(cameraPos_mat4ID, 1, GL_FALSE, &mvp[0][0]);
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
