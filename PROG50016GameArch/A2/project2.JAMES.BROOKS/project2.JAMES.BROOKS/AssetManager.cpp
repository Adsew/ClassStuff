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
#include "AssetManager.h"


void AssetManager::initialize() {

    assetCreate.clear();
}

void AssetManager::update() {

    for (std::map<std::string, std::shared_ptr<Asset>>::iterator iter = assets.begin();
        iter != assets.end();
        iter++) {

        if ((*iter).second.use_count() == 1) {

            assets.erase(iter);
        }
    }
}

void AssetManager::addAssetType(const char *name, std::function<Asset *(unsigned int)> creationFunc) {

    assetCreate[name] = creationFunc;
}

std::weak_ptr<Asset> AssetManager::getAsset(const char *assetName) {

    try {

        return assets.at(assetName);
    }
    catch (...) {

        if (loadAsset(assetName)) {

            try {

                return assets.at(assetName);
            }
            catch (...) {

                DEBUG_LOG("AssetManager: Asset loaded incorrectly.");
            }
        }
    }

    return std::weak_ptr<Asset>();
}

bool AssetManager::loadAsset(const char *assetName) {
    
    std::unique_ptr<FileSystem::FileAccessor> accessor = FileSystem::Instance().useFile("AssetsList");

    FileSystem::Instance().traverseToElement(accessor, "Assets");

    // Check asset exists
    if (FileSystem::Instance().traverseToElement(accessor, assetName)) {

        Asset *loadedAsset = NULL;
        std::string assetType;
        
        FileSystem::Instance().getAttribute(accessor, "type", assetType);

        try {

            loadedAsset = assetCreate.at(assetType)(Object::generateID());
        }
        catch (...) {

            DEBUG_LOG("AssetManager: Asset does not exist. Failed to load.")
        }

        if (loadedAsset != NULL) {

            loadedAsset->setName(assetName);

            loadedAsset->load(accessor);

            assets[assetName] = std::shared_ptr<Asset>(loadedAsset);

            return true;
        }
    }

    return false;
}
