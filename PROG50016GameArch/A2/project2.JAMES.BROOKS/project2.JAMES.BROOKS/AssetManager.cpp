/*
Student: James Brooks
Class: Game Architecture

File: AssetManager.cpp

Class: AssetManager

Description: Manages all assets created during the course of the game. Responsible for
    deleting and creating assets.
*/


#include "Core.h"

#include "Asset.h"
#include "TextureAsset.h"
#include "AssetManager.h"


void AssetManager::initialize() {

    assetCreate.clear();
}

void AssetManager::update() {

    for (std::list<std::shared_ptr<Asset>>::iterator iter = assets.begin();
        iter != assets.end();
        iter++) {

        if ((*iter).use_count() == 1) {

            assets.erase(iter);
        }
    }
}

void AssetManager::addAsset(Asset *asset) {

    if (asset != NULL) {

        //assets.push_back(asset);
    }
}

void AssetManager::RemoveAsset(Asset *asset) {

    if (asset != NULL) {

        for (std::list<std::shared_ptr<Asset>>::iterator iter = assets.begin();
            iter != assets.end();
            iter++) {

            if (*(*iter).get() == *asset) {

                assets.erase(iter);
            }
        }
    }
}

void AssetManager::loadAsset(const char *assetName) {
    
    std::unique_ptr<FileSystem::FileAccessor> accessor = FileSystem::Instance().useFile(assetFile);

    FileSystem::Instance().traverseToElement(accessor, "Assets");

    // Check asset exists
    if (FileSystem::Instance().traverseToElement(accessor, assetName)) {

        Asset *loadedAsset = NULL;
        std::string assetType;
        
        FileSystem::Instance().getAttribute(accessor, "type", assetType);

        try {

            loadedAsset = assetCreate.at(assetType)();
        }
        catch (...) {

            DEBUG_LOG("AssetManager: Asset does not exist. Failed to load.")
        }

        if (loadedAsset != NULL) {

            loadedAsset->load(accessor);

            // PUT INTO SHARED POINTER AND GIVE BACK TO LOADING COMPONENT
        }
    }
}
