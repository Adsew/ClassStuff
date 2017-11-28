#pragma once


#include <list>
#include <map>
#include <functional>

#include "tinyxml2.h"
#include "ISystem.h"


class Asset;


class AssetManager : public ISystem {

private:

	std::list<Asset*> assets;
    std::map<std::string, std::function<Asset *()>> assetCreate;

public:

	inline static AssetManager &Instance()
	{
		static AssetManager instance;

		return instance;
	}

private:

    AssetManager() = default;

    ~AssetManager() = default;

    AssetManager(const AssetManager& other) = default;

    friend class GameEngine;

protected:

	void initialize() override;

    void update(float _deltaTime) override;

public:

    void addAsset(Asset *asset);

    void RemoveAsset(Asset *asset);

    void load(tinyxml2::XMLElement *element);
};

