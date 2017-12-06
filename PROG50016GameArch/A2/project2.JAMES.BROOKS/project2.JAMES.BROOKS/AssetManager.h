#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: AssetManager.h

Class: AssetManager

Description: Manages all assets created during the course of the game. Responsible for
    deleting and creating assets.
*/


#include "ISystem.h"


class Asset;


class AssetManager : public ISystem {

    friend class GameEngine;


    /***** Variables *****/

private:

	std::list<Asset*> assets;

    std::map<std::string, std::function<Asset *()>> assetCreate;


    /***** Functions *****/

private:

    AssetManager() = default;

    ~AssetManager() = default;

    AssetManager(const AssetManager& other) = default;

protected:

	void initialize() override;

    void update() override;

public:

    inline static AssetManager &Instance() {

        static AssetManager instance;

        return instance;
    }

    void addAsset(Asset *asset);

    void RemoveAsset(Asset *asset);

    void load(tinyxml2::XMLElement *element);
};

#endif // !ASSET_MANAGER_H
