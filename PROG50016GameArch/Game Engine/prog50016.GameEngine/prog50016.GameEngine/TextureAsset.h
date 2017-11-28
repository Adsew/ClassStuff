#pragma once


#include "tinyxml2.h"
#include "Asset.h"


/// <summary>
/// TextureAsset Class
/// </summary>
class TextureAsset : public Asset {

private:

    std::string fileName;

public:

    static Asset *create() { return new TextureAsset(); }

    TextureAsset();
    
    virtual ~TextureAsset();

    void load(tinyxml2::XMLElement *element) override;
};

