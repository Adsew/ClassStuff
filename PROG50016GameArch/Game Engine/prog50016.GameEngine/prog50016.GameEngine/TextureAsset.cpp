#include "TextureAsset.h"


TextureAsset::TextureAsset()
{
}

TextureAsset::~TextureAsset()
{
}

void TextureAsset::load(XMLElement * _textureElement)
{
	XMLElement *element = _textureElement->FirstChildElement("filename");
	if (element == nullptr)
	{
		std::cout << "Cannot finfd texture filename for TextureAsset" << std::endl;
		return;
	}

	fileName = element->GetText();

	// More later when we 
}
