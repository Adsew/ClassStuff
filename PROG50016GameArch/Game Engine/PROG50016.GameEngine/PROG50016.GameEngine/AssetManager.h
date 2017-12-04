#pragma once

#include <list>
#include <functional>
#include <map>

#include "ISystem.h"

class Asset;

class AssetManager : public ISystem
{
private:
	std::list<Asset*> assets;
	std::map<std::string, std::function<Asset*()>> assetCreate;

public:
	inline static AssetManager& Instance()
	{
		static AssetManager instance;
		return instance;
	}

	void load(XMLElement* _assetManagerElement);

protected:
	void initialize() override;
	void update(float _deltaTime) override;

private:
	AssetManager() = default;
	~AssetManager() = default;
	AssetManager(const AssetManager& other) = default;

	friend class GameEngine;
};

