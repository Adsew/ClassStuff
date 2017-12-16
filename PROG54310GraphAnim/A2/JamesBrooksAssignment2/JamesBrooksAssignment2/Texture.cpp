/*
File: Texture.cpp

Student: James Brooks

Class: Texture

Description: Holds the texture location and data to be used by a model for rendering.
*/


#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <iostream>

#include "Texture.h"


Texture::Texture(const char *fileLoc) {

    textureLoc = SOIL_load_OGL_texture(
        fileLoc,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
    if (textureLoc != NULL) {

        glBindTexture(GL_TEXTURE_2D, textureLoc);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {

        std::cout << "SOIL Failed to load image\n" << SOIL_last_result();

        errorOccured = true;
    }

    errorOccured = false;
}


Texture::~Texture() {

    glDeleteTextures(1, &textureLoc);
}

void Texture::activateTexture() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureLoc);
}

bool Texture::error() {

    return errorOccured;
}
