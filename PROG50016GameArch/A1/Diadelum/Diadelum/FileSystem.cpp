/*
Student: James Brooks
Class: Game Architecture

File: FileSystem.cpp

Class: FileSystem

Description: Manages the input and output of files used by the game
*/


#include "tinyxml2.h"
#include "FileSystem.h"


using namespace tinyxml2;


FileSystem::FileSystem() {

    activeAsset = NULL;
    activeElem = NULL;

    initialized = false;
}

FileSystem::FileSystem(FileSystem &fs) {}

FileSystem::~FileSystem() {

    for (std::map<std::string, XMLDocument *>::iterator iter = assets.begin();
        iter != assets.end();
        iter++) {

        delete (*iter).second;
        (*iter).second = NULL;
    }

    activeAsset = NULL;
    activeElem = NULL;
}

FileSystem &FileSystem::operator=(FileSystem &fs) { return fs; }

// Initialize the file system to a usable state
bool FileSystem::initialize(const char *settingsLoc) {

    XMLDocument settingsFile;
    settingsFile.LoadFile(settingsLoc);

    if (settingsFile.Error() == false) {

        XMLNode *settings = settingsFile.FirstChildElement("Settings");

        if (settings != NULL) {

            // Get game engine settings
            XMLElement *assetsNode = settings->FirstChildElement("AssetFiles");

            if (assetsNode != NULL) {

                XMLDocument *asset = NULL;

                for (XMLElement *assetFile = assetsNode->FirstChildElement();
                    assetFile != NULL;
                    assetFile = assetFile->NextSiblingElement()) {

                    if (assetFile->Attribute("file") != NULL && assetFile->Attribute("name") != NULL) {

                        asset = new XMLDocument();

                        asset->LoadFile(assetFile->Attribute("file"));

                        if (asset->Error() == false) {

                            assets[assetFile->Attribute("name")] = asset;
                        }
                        else {

                            delete asset;
                        }
                    }
                }
            }
        }
    }

    if (assets.size() > 0) {

        initialized = true;

        return initialized;
    }

    return false;
}

// Initialize the file system to a usable state
void FileSystem::initialize(std::string &settingsLoc) {

    this->initialize(settingsLoc.c_str());
}

// Set the file to be used for loading
bool FileSystem::useFile(const char *fileRef) {

    try {

        activeAsset = assets.at(fileRef);
        activeElem = NULL;

        return true;
    }
    catch (const std::out_of_range &ex) {
    
        activeAsset = NULL;
        activeElem = NULL;
    }

    return false;
}

// Set the file to be used for loading
bool FileSystem::useFile(std::string &fileRef) {

    return this->useFile(fileRef.c_str());
}

// Changes from current node to a contained element
bool FileSystem::traverseToElement(const char *elem) {

    if (activeAsset != NULL) {

        XMLElement *temp = activeElem;

        if (activeElem == NULL) {

            activeElem = activeAsset->FirstChildElement(elem);
        }
        else {

            activeElem = activeElem->FirstChildElement(elem);
        }

        if (activeElem != NULL) {

            return true;
        }
        else {

            activeElem = temp;
        }
    }

    return false;
}

// Changes from current node to a contained element
bool FileSystem::traverseToElement(std::string &elem) {

    return this->traverseToElement(elem.c_str());
}

// Changes from current element to the next element of same parent
bool FileSystem::traverseToSyblingElement() {

    if (activeAsset != NULL) {
        if (activeElem != NULL) {

            XMLElement *temp = activeElem;

            activeElem = activeElem->NextSiblingElement();

            if (activeElem != NULL) {

                return true;
            }
            else {

                activeElem = temp;
            }
        }
    }

    return false;
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(const char *name, std::string &val) {

    if (activeElem != NULL) {
        if (activeElem->Attribute(name) != 0) {

            val = activeElem->Attribute(name);

            return true;
        }
    }

    return false;
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(std::string &name, std::string &val) {

    return this->getAttribute(name.c_str(), val);
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(const char *name, int &val) {

    if (activeElem != NULL) {
        if (activeElem->Attribute(name) != 0) {

            val = activeElem->IntAttribute(name);

            return true;
        }
    }

    return false;
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(std::string &name, int &val) {

    return this->getAttribute(name.c_str(), val);
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(const char *name, float &val) {

    if (activeElem != NULL) {
        if (activeElem->Attribute(name) != 0) {

            val = activeElem->FloatAttribute(name);

            return true;
        }
    }

    return false;
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(std::string &name, float &val) {

    return this->getAttribute(name.c_str(), val);
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(const char *name, double &val) {

    if (activeElem != NULL) {
        if (activeElem->Attribute(name) != 0) {

            val = activeElem->DoubleAttribute(name);

            return true;
        }
    }

    return false;
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(std::string &name, double &val) {

    return this->getAttribute(name.c_str(), val);
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(const char *name, bool &val) {

    if (activeElem != NULL) {
        if (activeElem->Attribute(name) != 0) {

            val = activeElem->BoolAttribute(name);

            return true;
        }
    }

    return false;
}

// Get an attribute from the current element, if exists
bool FileSystem::getAttribute(std::string &name, bool &val) {

    return this->getAttribute(name.c_str(), val);
}
