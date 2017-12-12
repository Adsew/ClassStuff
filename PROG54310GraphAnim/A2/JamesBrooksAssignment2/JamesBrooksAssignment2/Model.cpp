/*
File: Model.cpp

Student: James Brooks

Class: Model

Description: This class can later be converted to true models which will hold
the vertex and colour data for the model. For now it holds my premade
arrays for that data and renders when called.
*/


#include <string>
#include <iostream>
#include <fstream>

#include "Model.h"


/* For the purpose of this exercise, it was easier to pass in static */
/* arrays stored elsewhere for the purpose of maintaining cleaner    */
/* code. In actual implementation we would pass in heap allocated    */
/* arrays and be deleted by the model at the end of the life span.   */
Model::Model(Shader &shader, GLfloat verts[], GLfloat cols[], int vCount) {
    
    vertCount = vCount;
    vertData = verts;
    colData = cols;

    glGenVertexArrays(1, &vertArrObj);
    glBindVertexArray(vertArrObj);

    //Vertex buffer
    glGenBuffers(1, &vertexBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), vertData, GL_STATIC_DRAW);
    shader.setVertexAttribute();
    
    // Colour buffer
    glGenBuffers(1, &colourBuff);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 4 * sizeof(GLfloat), colData, GL_STATIC_DRAW);
    shader.setColourAttribute();

    // Normal buffer (calculated first then buffered)
    normData = new GLfloat[vertCount * 3];

    // All models are triangles so we can gaurentee 3 verts per triangle
    if (vertCount % 9 == 0) {

        for (int i = 0; i < vertCount * 3; i = i + 9) {

            glm::vec3 triVec1(vertData[i] - vertData[i + 3], vertData[i + 1] - vertData[i + 4], vertData[i + 2] - vertData[i + 5]);
            glm::vec3 triVec2(vertData[i] - vertData[i + 6], vertData[i + 1] - vertData[i + 7], vertData[i + 2] - vertData[i + 8]);

            glm::vec3 triNorm = glm::cross(triVec1, triVec2);

            // Give the norm to each vertex
            for (int j = 0; j < 9; j = j + 3) {

                normData[i + j] = triNorm.x;
                normData[i + j + 1] = triNorm.y;
                normData[i + j + 2] = triNorm.z;
            }
        }
    }

    glGenBuffers(1, &normalBuff);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), normData, GL_STATIC_DRAW);
    shader.setNormalAttribute();

    needsDeletion = false;
}

/* Unlike the above, this constructor will dynamically allocate    */
/* the data arrays like they will be in final implementation. Thus */
/* they will be deleted in the constructor like normal.            */
Model::Model(Shader &shader, const char *file) {

    char ignore = ' ';

    std::ifstream inStream(file, std::ios::in);

    // File format is assumed correct
    if (inStream.is_open()) {

        inStream >> vertCount;
        
        vertData = new GLfloat[vertCount * 3];
        colData = new GLfloat[vertCount * 4];

        // Now read vertex and colour data
        for (int i = 0; i < vertCount * 3 && ignore != EOF; i += 3) {

            inStream >> vertData[i] >> ignore >> vertData[i+1] >> ignore >> vertData[i+2] >> ignore;
        }
        for (int i = 0; i < vertCount * 4 && ignore != EOF; i += 4) {

            inStream >> colData[i] >> ignore >> colData[i+1] >> ignore >> colData[i+2] >> ignore 
                >> colData[i+3] >> ignore;
        }

        inStream.close();

        glGenVertexArrays(1, &vertArrObj);
        glBindVertexArray(vertArrObj);

        //Vertex buffer
        glGenBuffers(1, &vertexBuff);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), vertData, GL_STATIC_DRAW);
        shader.setVertexAttribute();

        // Colour buffer
        glGenBuffers(1, &colourBuff);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 4 * sizeof(GLfloat), colData, GL_STATIC_DRAW);
        shader.setColourAttribute();

        // Normal buffer (calculated first then buffered)
        normData = new GLfloat[vertCount * 3];

        // All models are triangles so we can gaurentee 3 verts per triangle
        if (vertCount % 9 == 0) {

            for (int i = 0; i < vertCount * 3; i = i + 9) {

                glm::vec3 triVec1(vertData[i] - vertData[i + 3], vertData[i + 1] - vertData[i + 4], vertData[i + 2] - vertData[i + 5]);
                glm::vec3 triVec2(vertData[i] - vertData[i + 6], vertData[i + 1] - vertData[i + 7], vertData[i + 2] - vertData[i + 8]);

                glm::vec3 triNorm = glm::cross(triVec1, triVec2);

                // Give the norm to each vertex
                for (int j = 0; j < 9; j = j + 3) {

                    normData[i + j] = triNorm.x;
                    normData[i + j + 1] = triNorm.y;
                    normData[i + j + 2] = triNorm.z;
                }
            }
        }

        glGenBuffers(1, &normalBuff);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), normData, GL_STATIC_DRAW);
        shader.setNormalAttribute();

        needsDeletion = true;
    }
    else {

        std::cerr << "Could not open file " << file << ". File not found.\n";

        vertCount = 0;
        vertData = NULL;
        colData = NULL;

        needsDeletion = false;
    }
}

Model::~Model() {

    if (needsDeletion && vertData != NULL && colData != NULL) {

        delete vertData;
        delete colData;
    }

    delete normData;

    glDeleteBuffers(1, &vertexBuff);
    glDeleteBuffers(1, &normalBuff);
    glDeleteBuffers(1, &colourBuff);

    glDeleteVertexArrays(1, &vertArrObj);
}

/* Render the stored buffer using draw arrays */
void Model::render() {

    glBindVertexArray(vertArrObj);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
}