#include "AssetManager.h"
#include "TextureAsset.h"

void AssetManager::load(XMLElement * _assetManagerElement)
{
	XMLElement* assetElement = _assetManagerElement->FirstChildElement("Asset");
	while (assetElement != nullptr)
	{
		std::string attrib = assetElement->Attribute("class");
		auto iter = assetCreate.find(attrib);
		if (iter != assetCreate.end())
		{
			Asset* asset = (*iter).second();
			asset->load(assetElement);
			assets.push_back(asset);
		}

		assetElement = assetElement->NextSiblingElement("Asset");
	}
}

void AssetManager::initialize()
{
	assetCreate.emplace("TextureAsset", TextureAsset::_create);

	// For each texture asset you want you need to add here
	// ...
}

void AssetManager::update(float _deltaTime)
{
}
