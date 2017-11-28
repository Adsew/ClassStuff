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


    // Class Functions

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


    // Loading Functions

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

// Chamges from current node to the first child
bool FileSystem::traverseToChildElement() {

    if (activeAsset != NULL) {

        XMLElement *temp = activeElem;

        if (activeElem == NULL) {

            activeElem = activeAsset->FirstChildElement();
        }
        else {

            activeElem = activeElem->FirstChildElement();
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

// Changes from current element to the next element of same parent by name
bool FileSystem::traverseToSyblingElement(const char *syb) {

    if (activeAsset != NULL) {
        if (activeElem != NULL) {

            XMLElement *temp = activeElem;

            activeElem = activeElem->NextSiblingElement(syb);

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

// Changes from current element to the next element of same parent by name
bool FileSystem::traverseToSyblingElement(std::string &syb) {

    return this->traverseToSyblingElement(syb.c_str());
}

// Return from current tag to parent tag
bool FileSystem::traverseToParentElement() {

    if (activeElem != NULL) {

        XMLElement *temp = activeElem;

        XMLNode *parent = activeElem->Parent();

        activeElem = (XMLElement *)parent;

        if (activeElem != NULL) {

            return true;
        }
        else {

            activeElem = temp;
        }
    }

    return false;
}

// Get the text contained in the tags of the current element
bool FileSystem::getElementText(std::string &val) {

    if (activeElem != NULL) {
        
        val = activeElem->GetText();

        return true;
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


    // Saving Functions

    // Save the given file to the location/filename
bool FileSystem::saveFile(const char *refName, const char *fileName) {

    if (assets.find(refName) != assets.end()) {

        if (assets[refName]->SaveFile(fileName) == XML_SUCCESS) {

            return true;
        }
    }

    return false;
}

// Save the given file to the location/filename
bool FileSystem::saveFile(std::string &refName, std::string &fileName) {

    return this->saveFile(refName.c_str(), fileName.c_str());
}

    // Create a new asset file. Is not automatically saved
bool FileSystem::createTempFile(const char *refName) {

    if (assets.find(refName) == assets.end()) {

        XMLDocument *asset = new XMLDocument();

        if (asset->Error() == false) {

            assets[refName] = asset;

            activeAsset = asset;
            activeElem = NULL;

            return true;
        }
        else {

            delete asset;
        }
    }

    return false;
}

// Create a new asset file. Is not automatically saved
bool FileSystem::createTempFile(std::string &refName) {

    return this->createTempFile(refName.c_str());
}

// Load an existing file from location, returns false if doesn't exist
bool FileSystem::loadFile(const char *refName, const char *fileLoc) {

    // Ensure doesn't already exist
    if (assets.find(refName) == assets.end()) {

        XMLDocument *asset = new XMLDocument();

        asset->LoadFile(fileLoc);

        if (asset->Error() == false) {

            assets[refName] = asset;

            activeAsset = asset;
            activeElem = NULL;

            return true;
        }
        else {

            delete asset;
        }
    }

    return false;
}

// Load an existing file from location, returns false if doesn't exist
bool FileSystem::loadFile(std::string &refName, std::string &fileLoc) {

    return this->loadFile(refName.c_str(), fileLoc.c_str());
}

// Create a new element as a child of the current element
bool FileSystem::newElement(const char *name) {

    if (activeAsset != NULL) {

        XMLElement *newElem = activeAsset->NewElement(name);

        if (newElem != NULL) {

            if (activeElem != NULL) {

                activeElem->InsertEndChild(newElem);
            }
            else {

                activeAsset->InsertEndChild(newElem);
            }
            
            activeElem = newElem;

            return true;
        }
    }

    return false;
}

// Create a new element as a child of the current element
bool FileSystem::newElement(std::string &name) {

    return this->newElement(name.c_str());
}

// Add text to the current element
bool FileSystem::setElementText(const char *text) {

    if (activeElem != NULL) {

        activeElem->SetText(text);

        return true;
    }

    return false;
}

// Add text to the current element
bool FileSystem::setElementText(std::string &text) {

    return this->setElementText(text.c_str());
}

bool FileSystem::destroyCurrentElement() {

    if (activeElem != NULL) {

        XMLElement *temp = activeElem;

        XMLNode *parent = activeElem->Parent();

        activeElem = (XMLElement *)parent;

        // If the parent was NULL, the node is the doc, the final parent node, cant delete it
        if (activeElem != NULL) {

            temp->DeleteChildren();
            activeAsset->DeleteNode(temp);
            
            return true;
        }
        else {

            activeElem = temp;
        }
    }

    return false;
}
