/*
Student: James Brooks
Class: Game Architecture

File: AssetManager.h

Class: AssetManager

Description: Manages all assets created during the course of the game. Responsible for
    deleting and creating assets.
*/


#include "TextureAsset.h"
#include "AssetManager.h"


using namespace tinyxml2;


void AssetManager::initialize() {

    assetCreate["TextureAsset"] = TextureAsset::create;
}

void AssetManager::update(float _deltaTime) {


}

void AssetManager::addAsset(Asset *asset) {

    if (asset != NULL) {

        assets.push_back(asset);
    }
}

void AssetManager::RemoveAsset(Asset *asset) {

    if (asset != NULL) {

        for (std::list<Asset *>::iterator iter = assets.begin();
            iter != assets.end();
            iter++) {

            if (*iter == asset) {

                assets.erase(iter);
            }
        }
    }
}

void AssetManager::load(XMLElement *element) {

    XMLElement *assetElement = element->FirstChildElement("Asset");

    while (assetElement != NULL) {

        std::string attrib = assetElement->Attribute("class");

        auto iter = assetCreate.find(attrib);

        if (iter != assetCreate.end()) {

            Asset *tempAsset = iter->second();

            tempAsset->load(assetElement);

            this->addAsset(tempAsset);
        }

        assetElement = assetElement->NextSiblingElement("Asset");
    }
}
