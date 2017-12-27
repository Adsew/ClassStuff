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

    TextureAsset(unsigned int uniqueID);
    
    virtual ~TextureAsset();

    void load(std::unique_ptr<FileSystem::FileAccessor> element) override;
};

#endif // !TEXTURE_ASSET_H
