/*
File: Model.cpp

Student: James Brooks

Class: Model

Description: This class can later be converted to true models which will hold
the vertex and colour data for the model. For now it holds my premade
arrays for that data and renders when called.
*/


#include "Model.h"


Model::Model() {

    static const GLfloat gVertBuffData[]{

        // Grass using quad
        -3.0f, -0.7f, -2.0f,
        3.0f, -0.7f, -2.0f,
        3.0f, -0.7f, 3.0f,
        -3.0f, -0.7f, 3.0f,

        // Water using quad
        -0.4f, -0.7f, -2.0f,
        0.4f, -0.7f, -2.0f,
        0.15f, -0.7f, 3.0f,
        -0.15f, -0.7f, 3.0f,

        // Sun using triangle fan
        0.5f, 0.7f, 1.0f,
        0.5f, 1.0f, 1.0f,
        0.30f, 0.8f, 1.0f,
        0.25f, 0.7f, 1.0f,
        0.30f, 0.50f, 1.0f,
        0.5f, 0.4f, 1.0f,
        0.7f, 0.50f, 1.0f,
        0.75f, 0.7f, 1.0f,
        0.7f, 0.8f, 1.0f,
        0.5f, 1.0f, 1.0f,

        // Stickman using lines
        0.6f, -0.5f, 1.0f,      // Body
        0.65f, -0.3f, 1.0f,
        0.6f, -0.5f, 1.0f,      // Left Leg
        0.55f, -0.7f, 1.0f,
        0.6f, -0.5f, 1.0f,      // Right Leg
        0.65f, -0.7f, 1.0f,
        0.645f, -0.33f, 1.0f,   // Left Arm
        0.55f, -0.23f, 1.0f,
        0.645f, -0.33f, 1.0f,   // Right Arm
        0.75f, -0.43f, 1.0f,

        // Stickman head using quads
        0.72f, -0.2f, 1.0f,
        0.62f, -0.2f, 1.0f,
        0.62f, -0.3f, 1.0f,
        0.72f, -0.3f, 1.0f,

        // Staff using line, hollow quad, and point
        0.5f, -0.6f, 1.0f,
        0.57f, -0.04f, 1.0f,

        0.57f, -0.04f, 1.0f,
        0.61f, 0.0f, 1.0f,
        0.58f, 0.05f, 1.0f,
        0.54f, 0.01f, 1.0f,

        0.575f, 0.005f, 1.0f,

        // Ray of light using triangle
        0.5f, 0.7f, 1.0f,
        -0.9f, -0.1f, 2.0f,
        -0.3f, -0.9f, 2.0f,

        // Wizard hat using quad strip
        0.6f, -0.15f, 1.0f,
        0.78f, -0.3f, 1.0f,
        0.67f, -0.16f, 1.0f,
        0.74f, -0.22f, 1.0f,
        0.72f, -0.13f, 1.0f,
        0.76f, -0.12f, 1.0f,
        0.8f, -0.16f, 1.0f,
        0.8f, -0.16f, 1.0f,

        // Monster using polygon and quads
        -0.8f, -0.8f, 2.0f,         // Left leg
        -0.7f, -0.8f, 2.0f,
        -0.65f, -0.5f, 2.0f,
        -0.68f, -0.5f, 2.0f,

        -0.6f, -0.8f, 2.0f,         // Right leg
        -0.5f, -0.8f, 2.0f,
        -0.61f, -0.5f, 2.0f,
        -0.65f, -0.5f, 2.0f,

        -0.68f, -0.5f, 2.0f,        // Body
        -0.61f, -0.5f, 2.0f,
        -0.55f, -0.3f, 2.0f,
        -0.61f, -0.2f, 2.0f,
        -0.68f, -0.2f, 2.0f,
        -0.74f, -0.3f, 2.0f,

        -0.55f, -0.3f, 2.0f,        // Arm
        -0.61f, -0.25f, 2.0f,
        -0.35f, -0.1f, 2.0f,
        -0.3f, -0.15f, 2.0f,
        -0.35f, -0.2f, 2.0f,

        // Monster eyes using triangles
        -0.66f, -0.3f, 2.0f,
        -0.69f, -0.28f, 2.0f,
        -0.67f, -0.26f, 2.0f,

        -0.63f, -0.3f, 2.0f,
        -0.6f, -0.28f, 2.0f,
        -0.62f, -0.26f, 2.0f
    };

    static const GLfloat gColBuffData[]{

        // Grass
        0.10f, 0.55f, 0.13f, 1.0f,
        0.10f, 0.55f, 0.13f, 1.0f,
        0.12f, 0.66f, 0.15f, 1.0f,
        0.12f, 0.66f, 0.15f, 1.0f,

        // Water
        0.1f, 0.3f, 0.3f, 1.0f,
        0.1f, 0.3f, 0.3f, 1.0f,
        0.1f, 0.6f, 0.6f, 1.0f,
        0.1f, 0.6f, 0.6f, 1.0f,

        // Sun
        1.0f, 1.0f, 0.33f, 1.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        1.0f, 0.75f, 0.3f, 0.0f,

        // Stickman
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,

        // Staff
        0.447f, 0.24f, 0.0f, 1.0f,
        0.3f, 0.3f, 0.3f, 1.0f,

        0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.5f, 0.2f,

        // Ray of light
        1.0f, 1.0f, 0.33f, 1.0f,
        1.0f, 0.75f, 0.3f, 0.0f,
        0.12f, 0.66f, 0.15f, 0.0f,

        // Wizard hat
        0.4f, 0.8f, 0.8f, 1.0f,
        0.4f, 0.8f, 0.8f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,
        0.4f, 0.8f, 0.8f, 1.0f,
        0.4f, 0.8f, 0.8f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,
        0.12f, 0.6f, 0.6f, 1.0f,

        // Monster
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.5f,
        1.0f, 1.0f, 1.0f, 0.5f,
        1.0f, 1.0f, 1.0f, 0.5f,

        // Monster eyes
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f
    };

    glGenBuffers(1, &vertexBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertBuffData), gVertBuffData, GL_STATIC_DRAW);

    glGenBuffers(1, &colourBuff);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gColBuffData), gColBuffData, GL_STATIC_DRAW);
}

Model::~Model() {

    glDeleteBuffers(1, &vertexBuff);
    glDeleteBuffers(1, &colourBuff);
}

/* Render the stored buffer using draw arrays */
void Model::render(GLuint &vertexPos_modelSpaceID, GLuint &colourPos_vec4ID) {

    // Vertices buffer
    glEnableVertexAttribArray(vertexPos_modelSpaceID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
    glVertexAttribPointer(
        vertexPos_modelSpaceID, // The attribute we want to configure
        3,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized
        0,                      // stride
        (void*)0                // array buffer offset
    );


    // Colour buffer
    glEnableVertexAttribArray(colourPos_vec4ID);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuff);
    glVertexAttribPointer(
        colourPos_vec4ID,       // The attribute we want to configure
        4,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // normalized
        0,                      // stride
        (void*)0                // array buffer offset
    );

    // Begin drawing scene
    glDrawArrays(GL_QUADS, 0, 4);           // Drawing grass

    glDrawArrays(GL_QUADS, 4, 4);           // Drawing water

    glDrawArrays(GL_TRIANGLE_FAN, 8, 10);   // Drawing sun

    glLineWidth(6.0);
    glDrawArrays(GL_LINES, 18, 10);         // Drawing stickman

    glDrawArrays(GL_QUADS, 28, 4);         // Drawing stickman Head

    glDrawArrays(GL_LINES, 32, 2);          // Drawing Staff

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_QUADS, 34, 4);          // Drawing staff fixture
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_POINTS, 38, 1);         // Drawing staff power

    glDrawArrays(GL_TRIANGLES, 39, 3);      // Drawing ray of light

    glDrawArrays(GL_QUAD_STRIP, 42, 8);     // Drawing wizard hat

    glDrawArrays(GL_QUADS, 50, 4);          // Drawing monster left leg
    glDrawArrays(GL_QUADS, 54, 4);          // Drawing monster right leg
    glDrawArrays(GL_POLYGON, 58, 6);        // Drawing monster body
    glDrawArrays(GL_POLYGON, 64, 5);        // Drawing monster Arm

    glDrawArrays(GL_TRIANGLES, 69, 6);      // Drawing monster eyes

    // End drawing, disable buffers
    glDisableVertexAttribArray(vertexPos_modelSpaceID);
    glDisableVertexAttribArray(colourPos_vec4ID);
}