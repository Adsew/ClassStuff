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

#include "Texture.h"
#include "Model.h"


/* For the purpose of this exercise, it was easier to pass in static */
/* arrays stored elsewhere for the purpose of maintaining cleaner    */
/* code. In actual implementation we would pass in heap allocated    */
/* arrays and be deleted by the model at the end of the life span.   */
Model::Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], GLfloat texs[], int vCount, const char *textureLocation, const char *textureLocation2) {

    texCount = 0;

    vertCount = vCount;
    vertData = verts;
    normData = norms;
    colData = cols;
    texData = texs;

    glGenVertexArrays(1, &vertArrObj);
    glBindVertexArray(vertArrObj);

    //Vertex buffer
    glGenBuffers(1, &vertexBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), vertData, GL_STATIC_DRAW);
    shader.setVertexAttribute();

    // Normal buffer
    glGenBuffers(1, &normalBuff);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), normData, GL_STATIC_DRAW);
    shader.setNormalAttribute();

    // Colour buffer
    glGenBuffers(1, &colourBuff);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 4 * sizeof(GLfloat), colData, GL_STATIC_DRAW);
    shader.setColourAttribute();

    needsDeletion = false;

    // Texture buffer
    glGenBuffers(1, &textureBuff);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 2 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
    shader.setTextureCoordAttribute();

    texNeedsDeletion = false;

    // Texture loading
    if (textureLocation != NULL) {

        tex1 = new Texture(textureLocation);

        if (tex1->error()) {

            delete tex1;
            tex1 = NULL;
        }
        else {

            texCount++;
        }
    }
    if (textureLocation2 != NULL) {

        tex2 = new Texture(textureLocation2);

        if (tex2->error()) {

            delete tex2;
            tex2 = NULL;
        }
        else {

            texCount++;
        }
    }
}

/* For the purpose of this exercise, it was easier to pass in static */
/* arrays stored elsewhere for the purpose of maintaining cleaner    */
/* code. In actual implementation we would pass in heap allocated    */
/* arrays and be deleted by the model at the end of the life span.   */
Model::Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], int vCount, const char *textureLocation, const char *textureLocation2) {
    
    texCount = 0;

    vertCount = vCount;
    vertData = verts;
    normData = norms;
    colData = cols;

    glGenVertexArrays(1, &vertArrObj);
    glBindVertexArray(vertArrObj);

    //Vertex buffer
    glGenBuffers(1, &vertexBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), vertData, GL_STATIC_DRAW);
    shader.setVertexAttribute();
    
    // Normal buffer
    glGenBuffers(1, &normalBuff);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), normData, GL_STATIC_DRAW);
    shader.setNormalAttribute();

    // Colour buffer
    glGenBuffers(1, &colourBuff);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 4 * sizeof(GLfloat), colData, GL_STATIC_DRAW);
    shader.setColourAttribute();

    needsDeletion = false;

    // Texture buffer
    glGenBuffers(1, &textureBuff);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 2 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
    shader.setTextureCoordAttribute();

    // Setup Texture Coords Dynamically
    float increment = 1.0f / vertCount * 50.0f;
    float value = 0.0f;

    texData = new GLfloat[vertCount * 2];

    for (int i = 0; i < vertCount * 2; i += 2) {

        texData[i] = value;
        texData[i + 1] = 1.0f - value;

        value += increment;
    }

    texNeedsDeletion = true;

    // Texture loading
    if (textureLocation != NULL) {

        tex1 = new Texture(textureLocation);

        if (tex1->error()) {

            delete tex1;
            tex1 = NULL;
        }
        else {

            texCount++;
        }
    }
    if (textureLocation2 != NULL) {

        tex2 = new Texture(textureLocation2);

        if (tex2->error()) {

            delete tex2;
            tex2 = NULL;
        }
        else {

            texCount++;
        }
    }
}

/* For the purpose of this exercise, it was easier to pass in static */
/* arrays stored elsewhere for the purpose of maintaining cleaner    */
/* code. In actual implementation we would pass in heap allocated    */
/* arrays and be deleted by the model at the end of the life span.   */
Model::Model(Shader &shader, GLfloat verts[], GLfloat norms[], GLfloat cols[], int vCount) {

    texCount = 0;

    tex1 = NULL;
    tex2 = NULL;

    vertCount = vCount;
    vertData = verts;
    normData = norms;
    colData = cols;

    // Setup Texture Coords Dynamically
    float increment = 1.0f / vertCount;
    float value = 0.0f;

    texData = new GLfloat[vertCount * 2];

    for (int i = 0; i < vertCount * 2; i += 2) {

        texData[i] = value;
        texData[i + 1] = 1.0f - value;

        value += increment;
    }

    glGenVertexArrays(1, &vertArrObj);
    glBindVertexArray(vertArrObj);

    //Vertex buffer
    glGenBuffers(1, &vertexBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), vertData, GL_STATIC_DRAW);
    shader.setVertexAttribute();

    // Normal buffer
    glGenBuffers(1, &normalBuff);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), normData, GL_STATIC_DRAW);
    shader.setNormalAttribute();

    // Colour buffer
    glGenBuffers(1, &colourBuff);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 4 * sizeof(GLfloat), colData, GL_STATIC_DRAW);
    shader.setColourAttribute();

    needsDeletion = false;

    // Texture buffer
    glGenBuffers(1, &textureBuff);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuff);
    glBufferData(GL_ARRAY_BUFFER, vertCount * 2 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
    shader.setTextureCoordAttribute();

    texNeedsDeletion = true;
}

/* Unlike the above, this constructor will dynamically allocate    */
/* the data arrays like they will be in final implementation. Thus */
/* they will be deleted in the constructor like normal.            */
Model::Model(Shader &shader, const char *file, const char *textureLocation, const char *textureLocation2) {

    char ignore = ' ';

    std::ifstream inStream(file, std::ios::in);

    texCount = 0;

    // File format is assumed correct
    if (inStream.is_open()) {

        inStream >> vertCount;

        vertData = new GLfloat[vertCount * 3];
        normData = new GLfloat[vertCount * 3];
        colData = new GLfloat[vertCount * 4];

        // Now read vertex, norm, and colour data
        for (int i = 0; i < vertCount * 3 && ignore != EOF; i += 3) {

            inStream >> vertData[i] >> ignore >> vertData[i + 1] >> ignore >> vertData[i + 2] >> ignore;
        }
        for (int i = 0; i < vertCount * 3 && ignore != EOF; i += 3) {

            inStream >> normData[i] >> ignore >> normData[i + 1] >> ignore >> normData[i + 2] >> ignore;
        }
        for (int i = 0; i < vertCount * 4 && ignore != EOF; i += 4) {

            inStream >> colData[i] >> ignore >> colData[i + 1] >> ignore >> colData[i + 2] >> ignore
                >> colData[i + 3] >> ignore;
        }

        inStream.close();

        // Setup Texture Coords Dynamically
        float increment = 1.0f / vertCount * 50.0f;
        float value = 0.0f;

        texData = new GLfloat[vertCount * 2];

        for (int i = 0; i < vertCount * 2; i += 2) {

            texData[i] = value;
            texData[i+1] = 1.0f - value;

            value += increment;
        }

        glGenVertexArrays(1, &vertArrObj);
        glBindVertexArray(vertArrObj);

        //Vertex buffer
        glGenBuffers(1, &vertexBuff);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), vertData, GL_STATIC_DRAW);
        shader.setVertexAttribute();

        // Normal buffer
        glGenBuffers(1, &normalBuff);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), normData, GL_STATIC_DRAW);
        shader.setNormalAttribute();

        // Colour buffer
        glGenBuffers(1, &colourBuff);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 4 * sizeof(GLfloat), colData, GL_STATIC_DRAW);
        shader.setColourAttribute();

        needsDeletion = true;

        // Texture buffer
        glGenBuffers(1, &textureBuff);
        glBindBuffer(GL_ARRAY_BUFFER, textureBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 2 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
        shader.setTextureCoordAttribute();

        texNeedsDeletion = true;

        // Texture loading
        if (textureLocation != NULL) {

            tex1 = new Texture(textureLocation);

            if (tex1->error()) {

                delete tex1;
                tex1 = NULL;
            }
            else {

                texCount++;
            }
        }
        if (textureLocation2 != NULL) {

            tex2 = new Texture(textureLocation2);

            if (tex2->error()) {

                delete tex2;
                tex2 = NULL;
            }
            else {

                texCount++;
            }
        }
    }
    else {

        std::cerr << "Could not open file " << file << ". File not found.\n";

        vertCount = 0;
        vertData = NULL;
        normData = NULL;
        colData = NULL;

        needsDeletion = false;
    }
}

/* Unlike the above, this constructor will dynamically allocate    */
/* the data arrays like they will be in final implementation. Thus */
/* they will be deleted in the constructor like normal.            */
Model::Model(Shader &shader, const char *file) {

    texCount = 0;

    tex1 = NULL;
    tex2 = NULL;

    char ignore = ' ';

    std::ifstream inStream(file, std::ios::in);

    // File format is assumed correct
    if (inStream.is_open()) {

        inStream >> vertCount;
        
        vertData = new GLfloat[vertCount * 3];
        normData = new GLfloat[vertCount * 3];
        colData = new GLfloat[vertCount * 4];

        // Now read vertex, norm, and colour data
        for (int i = 0; i < vertCount * 3 && ignore != EOF; i += 3) {

            inStream >> vertData[i] >> ignore >> vertData[i+1] >> ignore >> vertData[i+2] >> ignore;
        }
        for (int i = 0; i < vertCount * 3 && ignore != EOF; i += 3) {

            inStream >> normData[i] >> ignore >> normData[i + 1] >> ignore >> normData[i + 2] >> ignore;
        }
        for (int i = 0; i < vertCount * 4 && ignore != EOF; i += 4) {

            inStream >> colData[i] >> ignore >> colData[i+1] >> ignore >> colData[i+2] >> ignore 
                >> colData[i+3] >> ignore;
        }

        // Setup Texture Coords Dynamically
        float increment = 1.0f / vertCount;
        float value = 0.0f;

        texData = new GLfloat[vertCount * 2];

        for (int i = 0; i < vertCount * 2; i += 2) {

            texData[i] = value;
            texData[i + 1] = 1.0f - value;

            value += increment;
        }

        inStream.close();

        glGenVertexArrays(1, &vertArrObj);
        glBindVertexArray(vertArrObj);

        //Vertex buffer
        glGenBuffers(1, &vertexBuff);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), vertData, GL_STATIC_DRAW);
        shader.setVertexAttribute();

        // Normal buffer
        glGenBuffers(1, &normalBuff);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(GLfloat), normData, GL_STATIC_DRAW);
        shader.setNormalAttribute();

        // Colour buffer
        glGenBuffers(1, &colourBuff);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 4 * sizeof(GLfloat), colData, GL_STATIC_DRAW);
        shader.setColourAttribute();

        needsDeletion = true;

        // Texture buffer
        glGenBuffers(1, &textureBuff);
        glBindBuffer(GL_ARRAY_BUFFER, textureBuff);
        glBufferData(GL_ARRAY_BUFFER, vertCount * 2 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
        shader.setTextureCoordAttribute();

        texNeedsDeletion = true;
    }
    else {

        std::cerr << "Could not open file " << file << ". File not found.\n";

        vertCount = 0;
        vertData = NULL;
        normData = NULL;
        colData = NULL;

        needsDeletion = false;
    }
}

Model::~Model() {

    if (needsDeletion) {

        delete vertData;
        delete normData;
        delete colData;
    }

    if (tex1 != NULL) {

        delete tex1;
    }

    if (tex2 != NULL) {

        delete tex2;
    }

    if (texNeedsDeletion) {

        delete texData;
    }
    
    glDeleteBuffers(1, &vertexBuff);
    glDeleteBuffers(1, &normalBuff);
    glDeleteBuffers(1, &colourBuff);
    glDeleteBuffers(1, &textureBuff);

    glDeleteVertexArrays(1, &vertArrObj);
}

/* Render the stored buffer using draw arrays */
void Model::render(Shader &shader) {

    shader.setTextureCountAttribute(texCount);

    if (tex1 != NULL) {

        tex1->activateTexture(GL_TEXTURE0);
    }
    if (tex2 != NULL) {

        tex2->activateTexture(GL_TEXTURE1);
    }

    glBindVertexArray(vertArrObj);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
}