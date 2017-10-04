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
}


Shader::~Shader() {

    glDeleteProgram(programID);
}

GLuint Shader::getProgramID() {

    // Link the program
    std::cout << "Linking program\n";

    programID = glCreateProgram();

    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);

    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {

        GLchar *progErrMsg = new GLchar[infoLogLen + 1];
        glGetProgramInfoLog(programID, infoLogLen, NULL, &progErrMsg[0]);
        std::cerr << &progErrMsg[0] << "\n";
        delete progErrMsg;
    }

    glDetachShader(programID, vertShaderID);
    glDetachShader(programID, fragShaderID);

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);

    // Enable alpha values
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Get a handle for our buffers
    vertexPos_modelSpaceID = glGetAttribLocation(progID, "vertexPosition_modelspace");
    colourPos_vec4ID = glGetAttribLocation(progID, "colour");
}

/* Load shader files and initialize openGL shader data */
bool Shader::addShader(std::string shaderFile, __glewCreateShader shaderType) {

    std::string vertexShaderLoc = "VertexShader.shader";
    std::string fragShaderLoc = "FragmentShader.shader";

    GLint result = GL_FALSE;
    int infoLogLen = 0;

    // Create the shaders
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile Vertex Shader
    ShaderLoader vertLoader(vertexShaderLoc);
    std::string vertShaderCode = vertLoader.getText();
    char const *vertSourcePointer = vertShaderCode.c_str();
    glShaderSource(vertShaderID, 1, &vertSourcePointer, NULL);
    glCompileShader(vertShaderID);

    // Check Vertex Shader
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {

        GLchar *vertShaderErrMsg = new GLchar[infoLogLen + 1];
        glGetShaderInfoLog(vertShaderID, infoLogLen, NULL, &vertShaderErrMsg[0]);
        std::cerr << &vertShaderErrMsg[0] << "\n";
        delete vertShaderErrMsg;
    }

    // Compile Fragment Shader
    ShaderLoader fragLoader(fragShaderLoc);
    std::string fragShaderCode = fragLoader.getText();
    char const * fragSourcePointer = fragShaderCode.c_str();
    glShaderSource(fragShaderID, 1, &fragSourcePointer, NULL);
    glCompileShader(fragShaderID);

    // Check Fragment Shader
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &infoLogLen);

    if (infoLogLen > 0) {

        GLchar *fragShaderErrMsg = new GLchar[infoLogLen + 1];
        glGetShaderInfoLog(fragShaderID, infoLogLen, NULL, &fragShaderErrMsg[0]);
        std::cerr << &fragShaderErrMsg[0] << "\n";
        delete fragShaderErrMsg;
    }

    return true;
}
