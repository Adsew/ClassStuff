#ifndef ASSET_H
#define ASSET_H

/*
Student: James Brooks
Class: Game Architecture

File: Asset.h

Class: Asset

Description: A base class for all future assets of any time to be created.
*/


#include "Object.h"


class Asset : public Object {

    friend class AssetManager;

    /***** Variables *****/

private:

    std::string name;


    /***** Functions *****/

protected:

	Asset(unsigned int uniqueID);

	virtual ~Asset();

    void initialize() override final {}

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> element) = 0;

public:

    void setName(const char *n);
};

#endif // !ASSET_H
