#pragma once


#include <list>

#include "tinyxml2.h"
#include "ISystem.h"


class Asset;


class AssetManager : public ISystem {

private:

	std::list<Asset*> assets;

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

    void addAsset(Asset *component);

    void RemoveAsset(Asset *component);

    void load(tinyxml2::XMLElement *element);
};

