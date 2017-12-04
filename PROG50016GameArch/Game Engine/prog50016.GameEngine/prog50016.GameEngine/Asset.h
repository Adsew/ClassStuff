#pragma once

#include "Object.h"

/// <summary>
/// Asset Class
/// </summary>
class Asset : public Object
{
protected:
	Asset();
	~Asset();

	virtual void load(XMLElement* _element) = 0;

private:
	friend class AssetManager;
};

