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


class Light;


class Shader {

private:

    /***** Structs for Shaders *****/

    struct LightVariables {

        GLuint colour;
        GLuint position;
        GLuint direction;

        GLuint ambientStrength;
        GLuint specularStrength;

        GLuint specularSize;
    };


    /***** Variables *****/

    GLuint programID;   // Program's ID position

    GLuint vertexPos_modelSpaceID;
    GLuint normalPos_vec3ID;
    GLuint colourPos_vec4ID;
    GLuint cameraMVPPos_mat4ID;
    GLuint cameraPPos_vec3ID;
    LightVariables *lightPos_structID;
    GLuint lightCountPos_int;

    int lightCount;

    bool modified;      // True if shader added since last compile, false after compile

    std::list<GLuint> shaderList;   // List of shaders successfully added to program


public:

    /***** Functions *****/

    Shader();

    ~Shader();

    /* Should always be called to get the most up to date Program ID */
    /* A copy of program ID held by user can become out of date      */
    GLuint getProgramID();

    /* Use the currently built shader program */
    void use();

    /* Generate the handles for the currently built shader program for all types */
    void generateHandles(const char *vertexVar, const char *normalVar, const char *colourVar, const char *cameraMVPVar, const char *cameraPosVar);

    /* Generate the vertex handle for the currently built shader program */
    void genHandleVertex(const char *vertexVar);

    /* Generate the normal handle for the currently built shader program */
    void genHandleNormal(const char *normalVar);

    /* Generate the colour handle for the currently built shader program */
    void genHandleColour(const char *colourVar);

    /* Generate the camera handle for the currently built shader program */
    void genHandleCamera(const char *cameraVar, const char *cameraPosVar);

    /* Generate handles for the amount of lights in the scene */
    void genHandleLights(const char *lightArrayStr, const char *lightCountStr, int maxNumLights);

    /* Sets the bound buffer to the vertex variable of the shader program */
    void setVertexAttribute();

    /* Sets the bound buffer to the normal variable of the shader program */
    void setNormalAttribute();

    /* Sets the bound buffer to the colour variable of the shader program */
    void setColourAttribute();

    /* Sets the camera matrix to the camera variable of the shader program */
    void setCameraAttribute(glm::mat4 &mvp, glm::vec3 &view);

    /* Set a single light attribute to its associated position in the shader program */
    /* orderNum is from 0 - (maxlights-1) to tell which light to set */
    void setLightAttribute(Light *light, int orderNum);

    /* Set the attribute to tell the shader how many lights are active */
    void setLightCountAttribute(int count);

    /* Add a shader to the shader program */
    bool addShader(std::string shaderFile, GLenum shaderType);
};

