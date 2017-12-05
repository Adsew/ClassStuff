#ifndef TEXTURE_ASSET_H
#define TEXTURE_ASSET_H


/*
Student: James Brooks
Class: Game Architecture

File: TextureAsset.h

Class: TextureAsset

Description: An asset that holds an image to be used as a texture.
*/


#include "Asset.h"


class TextureAsset : public Asset {

private:

    std::string fileName;

public:

    static Asset *create() { return new TextureAsset(); }

    TextureAsset();
    
    virtual ~TextureAsset();

    void load(tinyxml2::XMLElement *element) override;
};

#endif // !TEXTURE_ASSET_H
