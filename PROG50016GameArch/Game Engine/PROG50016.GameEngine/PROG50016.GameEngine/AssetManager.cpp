#include "AssetManager.h"


using namespace tinyxml2;


void AssetManager::initialize() {


}

void AssetManager::update(float _deltaTime) {


}

void AssetManager::addAsset(Asset *component) {

    if (component != NULL) {

        assets.push_back(component);
    }
}

void AssetManager::RemoveAsset(Asset *component) {

    if (component != NULL) {

        for (std::list<Asset *>::iterator iter = assets.begin();
            iter != assets.end();
            iter++) {

            if (*iter == component) {

                assets.erase(iter);
            }
        }
    }
}

void AssetManager::load(XMLElement *element) {


}
