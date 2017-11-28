#pragma once


#include "tinyxml2.h"
#include "Object.h"


/// <summary>
/// Asset Class
/// </summary>
class Asset : public Object {

    friend class AssetManager;

protected:

	Asset();

	virtual ~Asset();

    virtual void load(tinyxml2::XMLElement *element) = 0;
};

