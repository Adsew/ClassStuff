#ifndef ASSET_H
#define ASSET_H

/*
Student: James Brooks
Class: Game Architecture

File: Asset.h

Class: Asset

Description: A base class for all future assets of any time to be created.
*/


#include "tinyxml2.h"
#include "Object.h"


class Asset : public Object {

    friend class AssetManager;

protected:

	Asset();

	virtual ~Asset();

    virtual void load(tinyxml2::XMLElement *element) = 0;
};

#endif // !ASSET_H
