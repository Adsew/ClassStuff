/*
File: Shader.h

Student: James Brooks

Class: Shader

Description: This class will allow the addition of multiple shaders
to create a concatinated program shader.
*/


#include <iostream>
#include <string>

#include "Light.h"
#include "ShaderLoader.h"
#include "Shader.h"


Shader::Shader() {

    programID = 0;
    modified = false;

    lightPos_structID = NULL;
    lightCount = 0;
}


Shader::~Shader() {

    glDeleteProgram(programID);

    if (lightPos_structID != NULL) {

        delete lightPos_structID;
    }
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

/* Use the currently built shader program */
void Shader::use() {

    glUseProgram(this->getProgramID());
}

/* Generate the handles for the currently built shader program */
void Shader::generateHandles(const char *vertexVar, const char *normalVar, const char *colourVar, const char *cameraMVPVar, const char *cameraPosVar) {

    vertexPos_modelSpaceID = glGetAttribLocation(getProgramID(), vertexVar);
    normalPos_vec3ID = glGetAttribLocation(getProgramID(), normalVar);
    colourPos_vec4ID = glGetAttribLocation(getProgramID(), colourVar);
    cameraMVPPos_mat4ID = glGetUniformLocation(getProgramID(), cameraMVPVar);
    cameraPPos_vec3ID = glGetUniformLocation(getProgramID(), cameraPosVar);
}

/* Generate the vertex handle for the currently built shader program */
void Shader::genHandleVertex(const char *vertexVar) {

    vertexPos_modelSpaceID = glGetAttribLocation(getProgramID(), vertexVar);
}

/* Generate the normal handle for the currently built shader program */
void Shader::genHandleNormal(const char *normalVar) {

    normalPos_vec3ID = glGetAttribLocation(getProgramID(), normalVar);
}

/* Generate the colour handle for the currently built shader program */
void Shader::genHandleColour(const char *colourVar) {

    colourPos_vec4ID = glGetAttribLocation(getProgramID(), colourVar);
}

/* Generate the camera handle for the currently built shader program */
void Shader::genHandleCamera(const char *cameraMVPVar, const char *cameraPosVar) {

    cameraMVPPos_mat4ID = glGetUniformLocation(getProgramID(), cameraMVPVar);
    cameraPPos_vec3ID = glGetUniformLocation(getProgramID(), cameraPosVar);
}

/* Generate handles for the amount of lights in the scene */
void Shader::genHandleLights(const char *lightArrayStr, const char *lightCountStr, int maxNumLights) {

    lightPos_structID = new LightVariables[maxNumLights];
    lightCount = maxNumLights;

    for (int i = 0; i < maxNumLights; i++) {

        std::string lightVar = lightArrayStr + std::string("[") + std::to_string(i) + std::string("]");

        lightPos_structID[i].colour = glGetUniformLocation(getProgramID(), (lightVar + ".colour").c_str());
        lightPos_structID[i].position = glGetUniformLocation(getProgramID(), (lightVar + ".position").c_str());
        lightPos_structID[i].direction = glGetUniformLocation(getProgramID(), (lightVar + ".direction").c_str());

        lightPos_structID[i].ambientStrength = glGetUniformLocation(getProgramID(), (lightVar + ".ambient_str").c_str());
        lightPos_structID[i].specularStrength = glGetUniformLocation(getProgramID(), (lightVar + ".specular_str").c_str());
        lightPos_structID[i].specularSize = glGetUniformLocation(getProgramID(), (lightVar + ".specular_size").c_str());
    }

    lightCountPos_int = glGetUniformLocation(getProgramID(), lightCountStr);
}

/* Generate handles for two textures */
void Shader::genHandleTextures(const char *texture1, const char *texture2, const char *activeTextureCount) {

    texturePos_sample1 = glGetUniformLocation(getProgramID(), texture1);
    glUniform1i(texturePos_sample1, 0);

    texturePos_sample2 = glGetUniformLocation(getProgramID(), texture2);
    glUniform1i(texturePos_sample2, 1);

    textureCountPos_int = glGetUniformLocation(getProgramID(), activeTextureCount);
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

/* Sets the bound buffer to the normal variable of the shader program */
void Shader::setNormalAttribute() {

    glVertexAttribPointer(
        normalPos_vec3ID, // The attribute we want to configure
        3,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized
        0,                      // stride
        (void*)0                // array buffer offset
    );

    glEnableVertexAttribArray(normalPos_vec3ID);
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
void Shader::setCameraAttribute(glm::mat4 &mvp, glm::vec3 &view) {

    glUniformMatrix4fv(cameraMVPPos_mat4ID, 1, GL_FALSE, &mvp[0][0]);
    glUniform3fv(cameraPPos_vec3ID, 1, &view[0]);
}

/* Set a single light attribute to its associated position in the shader program */
/* orderNum is from 0 - (maxlights-1) to tell which light to set */
void Shader::setLightAttribute(Light *light, int orderNum) {

    if (orderNum < lightCount) {

        glUniform3fv(lightPos_structID[orderNum].colour, 1, &(light->colour[0]));
        glUniform3fv(lightPos_structID[orderNum].position, 1, &(light->position[0]));
        glUniform3fv(lightPos_structID[orderNum].direction, 1, &(light->direction[0]));

        glUniform1f(lightPos_structID[orderNum].ambientStrength, light->ambientStrength);
        glUniform1f(lightPos_structID[orderNum].specularStrength, light->specularStrength);

        glUniform1i(lightPos_structID[orderNum].specularSize, light->specularSize);
    }
}

/* Set the attribute to tell the shader how many lights are active */
void Shader::setLightCountAttribute(int count) {

    glUniform1i(lightCountPos_int, count);
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
