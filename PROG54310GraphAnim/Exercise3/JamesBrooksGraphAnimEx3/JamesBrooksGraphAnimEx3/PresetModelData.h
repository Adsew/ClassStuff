#pragma once

/*
A collection of static arrays used to showcase the array parameter constructor for models.
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>


/***** Vertices *****/


static GLfloat terrainVertData[]{

    // Grass using quad
    -3.0f, -0.7f, -2.0f,
    3.0f, -0.7f, -2.0f,
    3.0f, -0.7f, 3.0f,
    3.0f, -0.7f, 3.0f,
    -3.0f, -0.7f, 3.0f,
    -3.0f, -0.7f, -2.0f,

    // Water using quad
    -0.4f, -0.7f, -2.0f,
    0.4f, -0.7f, -2.0f,
    0.15f, -0.7f, 3.0f,
    0.15f, -0.7f, 3.0f,
    -0.15f, -0.7f, 3.0f,
    -0.4f, -0.7f, -2.0f,
};

static GLfloat sunVertData[]{
    
    0.5f, 0.7f, 1.0f,
    0.5f, 1.0f, 1.0f,
    0.30f, 0.8f, 1.0f,

    0.5f, 0.7f, 1.0f,
    0.30f, 0.8f, 1.0f,
    0.25f, 0.7f, 1.0f,

    0.5f, 0.7f, 1.0f,
    0.25f, 0.7f, 1.0f,
    0.30f, 0.50f, 1.0f,

    0.5f, 0.7f, 1.0f,
    0.30f, 0.50f, 1.0f,
    0.5f, 0.4f, 1.0f,

    0.5f, 0.7f, 1.0f,
    0.5f, 0.4f, 1.0f,
    0.7f, 0.50f, 1.0f,

    0.5f, 0.7f, 1.0f,
    0.7f, 0.50f, 1.0f,
    0.75f, 0.7f, 1.0f,

    0.5f, 0.7f, 1.0f,
    0.75f, 0.7f, 1.0f,
    0.7f, 0.8f, 1.0f,

    0.5f, 0.7f, 1.0f,
    0.7f, 0.8f, 1.0f,
    0.5f, 1.0f, 1.0f,
};

static GLfloat stickmanVertData[]{
    
    0.59f, -0.53f, 1.0f,    // Body
    0.61f, -0.29f, 1.0f,
    0.69f, -0.32f, 1.0f,

    0.595f, -0.48f, 1.0f,   // Left Leg
    0.57f, -0.7f, 1.0f,
    0.52f, -0.7f, 1.0f,

    0.595f, -0.48f, 1.0f,   // Right Leg
    0.67f, -0.7f, 1.0f,
    0.62f, -0.7f, 1.0f,

    0.645f, -0.34f, 1.0f,   // Left Arm
    0.55f, -0.23f, 1.0f,
    0.55f, -0.28f, 1.0f,

    0.645f, -0.3f, 1.0f,   // Right Arm
    0.75f, -0.42f, 1.0f,
    0.75f, -0.47f, 1.0f,

    0.72f, -0.2f, 1.0f,     // Head
    0.62f, -0.2f, 1.0f,
    0.62f, -0.3f, 1.0f,

    0.62f, -0.3f, 1.0f,
    0.72f, -0.3f, 1.0f,
    0.72f, -0.2f, 1.0f,
};

static GLfloat staffVertData[]{
    
    0.5f, -0.6f, 1.0f,      // staff
    0.57f, -0.04f, 1.0f,
    0.58f, -0.04f, 1.0f,

    0.58f, -0.04f, 1.0f,
    0.5f, -0.6f, 1.0f,
    0.51f, -0.6f, 1.0f,

    0.575f, -0.04f, 1.0f,   // Head
    0.615f, 0.0f, 1.0f,
    0.585f, 0.05f, 1.0f,

    0.585f, 0.05f, 1.0f,
    0.545f, 0.01f, 1.0f,
    0.575f, -0.04f, 1.0f,
};

//static GLfloat raylightVertData[]{
//    
//    0.5f, 0.7f, 1.0f,
//    -0.9f, -0.1f, 2.0f,
//    -0.3f, -0.9f, 2.0f,
//};

static GLfloat wizhatVertData[]{
    
    0.6f, -0.15f, 1.0f,
    0.78f, -0.3f, 1.0f,
    0.67f, -0.16f, 1.0f,

    0.78f, -0.3f, 1.0f,
    0.74f, -0.22f, 1.0f,
    0.67f, -0.16f, 1.0f,

    0.74f, -0.22f, 1.0f,
    0.67f, -0.16f, 1.0f,
    0.72f, -0.13f, 1.0f,

    0.74f, -0.22f, 1.0f,
    0.72f, -0.13f, 1.0f,
    0.76f, -0.12f, 1.0f,

    0.72f, -0.13f, 1.0f,
    0.76f, -0.12f, 1.0f,
    0.8f, -0.16f, 1.0f,
};

//static GLfloat monsterVertData[]{
//    
//    -0.8f, -0.8f, 2.0f,         // Left leg
//    -0.7f, -0.8f, 2.0f,
//    -0.65f, -0.5f, 2.0f,
//
//    -0.65f, -0.5f, 2.0f,
//    -0.68f, -0.5f, 2.0f,
//    -0.8f, -0.8f, 2.0f,
//
//    -0.6f, -0.8f, 2.0f,         // Right leg
//    -0.5f, -0.8f, 2.0f,
//    -0.61f, -0.5f, 2.0f,
//
//    -0.61f, -0.5f, 2.0f,
//    -0.65f, -0.5f, 2.0f,
//    -0.6f, -0.8f, 2.0f,
//
//    -0.68f, -0.5f, 2.0f,        // Body
//    -0.61f, -0.5f, 2.0f,
//    -0.55f, -0.3f, 2.0f,
//
//    -0.68f, -0.5f, 2.0f,
//    -0.61f, -0.2f, 2.0f,
//    -0.55f, -0.3f, 2.0f,
//
//    -0.61f, -0.2f, 2.0f,
//    -0.74f, -0.3f, 2.0f,
//    -0.68f, -0.5f, 2.0f,
//
//    -0.61f, -0.2f, 2.0f,
//    -0.68f, -0.2f, 2.0f,
//    -0.74f, -0.3f, 2.0f,
//
//    -0.55f, -0.3f, 2.0f,        // Arm
//    -0.61f, -0.25f, 2.0f,
//    -0.35f, -0.1f, 1.8f,
//    
//    -0.35f, -0.1f, 1.8f,
//    -0.3f, -0.15f, 1.8f,
//    -0.55f, -0.3f, 2.0f,
//
//    -0.66f, -0.3f, 2.0f,        // Eyes
//    -0.69f, -0.28f, 2.0f,
//    -0.67f, -0.26f, 2.0f,
//
//    -0.63f, -0.3f, 2.0f,
//    -0.6f, -0.28f, 2.0f,
//    -0.62f, -0.26f, 2.0f
//};



/***** Colours *****/


static GLfloat terrainColData[]{

    // Grass
    0.10f, 0.55f, 0.13f, 1.0f,
    0.10f, 0.55f, 0.13f, 1.0f,
    0.12f, 0.66f, 0.15f, 1.0f,
    0.12f, 0.66f, 0.15f, 1.0f,
    0.12f, 0.66f, 0.15f, 1.0f,
    0.10f, 0.55f, 0.13f, 1.0f,

    // Water
    0.1f, 0.3f, 0.3f, 1.0f,
    0.1f, 0.3f, 0.3f, 1.0f,
    0.1f, 0.6f, 0.6f, 1.0f,
    0.1f, 0.6f, 0.6f, 1.0f,
    0.1f, 0.6f, 0.6f, 1.0f,
    0.1f, 0.3f, 0.3f, 1.0f,
};

static GLfloat sunColData[]{
    
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 1.0f, 0.33f, 1.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
    1.0f, 0.75f, 0.3f, 0.0f,
};

static GLfloat stickmanColData[]{
    
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
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

static GLfloat staffColData[]{
    
    0.3f, 0.3f, 0.3f, 1.0f,
    0.447f, 0.24f, 0.0f, 1.0f,
    0.447f, 0.24f, 0.0f, 1.0f,
    0.447f, 0.24f, 0.0f, 1.0f,
    0.3f, 0.3f, 0.3f, 1.0f,
    0.3f, 0.3f, 0.3f, 1.0f,


    0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f, 1.0f,
};

//static GLfloat raylightColData[]{
//    
//    1.0f, 1.0f, 0.33f, 1.0f,
//    1.0f, 0.75f, 0.3f, 0.0f,
//    0.12f, 0.66f, 0.15f, 0.0f,
//};

static GLfloat wizhatColData[]{
    
    0.4f, 0.8f, 0.8f, 1.0f,
    0.4f, 0.8f, 0.8f, 1.0f,
    0.12f, 0.6f, 0.6f, 1.0f,

    0.4f, 0.8f, 0.8f, 1.0f,
    0.12f, 0.6f, 0.6f, 1.0f,
    0.12f, 0.6f, 0.6f, 1.0f,

    0.12f, 0.6f, 0.6f, 1.0f,
    0.12f, 0.6f, 0.6f, 1.0f,
    0.4f, 0.8f, 0.8f, 1.0f,

    0.12f, 0.6f, 0.6f, 1.0f,
    0.4f, 0.8f, 0.8f, 1.0f,
    0.4f, 0.8f, 0.8f, 1.0f,

    0.4f, 0.8f, 0.8f, 1.0f,
    0.4f, 0.8f, 0.8f, 1.0f,
    0.12f, 0.6f, 0.6f, 1.0f,
};

//static GLfloat monsterColData[]{
//    
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//
//    0.1f, 0.1f, 0.1f, 1.0f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//    1.0f, 1.0f, 1.0f, 0.2f,
//    1.0f, 1.0f, 1.0f, 0.2f,
//    1.0f, 1.0f, 1.0f, 0.2f,
//    0.1f, 0.1f, 0.1f, 1.0f,
//
//    1.0f, 0.0f, 0.0f, 1.0f,     // Eyes
//    1.0f, 0.0f, 0.0f, 1.0f,
//    1.0f, 0.0f, 0.0f, 1.0f,
//    1.0f, 0.0f, 0.0f, 1.0f,
//    1.0f, 0.0f, 0.0f, 1.0f,
//    1.0f, 0.0f, 0.0f, 1.0f
//};