#pragma once

/*
File: Texture.h

Student: James Brooks

Class: Texture

Description: Holds the texture location and data to be used by a model for rendering.
*/


class Texture {

private:

    unsigned int textureLoc;

    bool errorOccured;

public:
    
    Texture(const char *fileLoc);
    
    ~Texture();

    bool error();

    void activateTexture();
};

