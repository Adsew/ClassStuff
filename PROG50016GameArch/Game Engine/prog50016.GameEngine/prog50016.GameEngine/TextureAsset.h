#pragma once

#include "Asset.h"
#include <string>

class TextureAsset : public Asset
{
public:
	static Asset* _create() { return new TextureAsset(); }

	TextureAsset();
	~TextureAsset();

protected:
	void load(XMLElement* _element) override;

private:
	std::string fileName;

};

