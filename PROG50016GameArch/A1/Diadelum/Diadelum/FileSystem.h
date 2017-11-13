#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: FileSystem.h

Class: FileSystem

Description: Manages the input and output of files used by the game
*/


#include <string>
#include <map>


namespace tinyxml2 {
    class XMLDocument;
    class XMLElement;
}


class FileSystem {

private:

    /***** Variables *****/

    std::map<std::string, tinyxml2::XMLDocument *> assets;

    tinyxml2::XMLDocument *activeAsset;
    tinyxml2::XMLElement *activeElem;

    bool initialized;


    /****** Functions *****/

    FileSystem();

    FileSystem(FileSystem &fs);

    ~FileSystem();

    FileSystem &operator=(FileSystem &fs);

public:

    inline static FileSystem &Instance() {

        static FileSystem instance;

        return instance;
    }

    // Initialize the file system to a usable state
    bool initialize(const char *settingsLoc);

    // Initialize the file system to a usable state
    void initialize(std::string &settingsLoc);

    // Set the file to be used for loading
    bool useFile(const char *fileRef);

    // Set the file to be used for loading
    bool useFile(std::string &fileRef);

    // Changes from current node to a contained element
    bool traverseToElement(const char *elem);

    // Changes from current node to a contained element
    bool traverseToElement(std::string &elem);

    // Chamges from current node to the first child
    bool traverseToChildElement();

    // Changes from current element to the next element of same parent
    bool traverseToSyblingElement();

    // Changes from current element to the next element of same parent by name
    bool traverseToSyblingElement(const char *syb);

    // Changes from current element to the next element of same parent by name
    bool traverseToSyblingElement(std::string &syb);

    // Return from current tag to parent tag
    bool traverseToParentElement();

    // Get the text contained in the tags of the current element
    bool getElementText(std::string &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, std::string &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(std::string &name, std::string &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, int &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(std::string &name, int &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, float &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(std::string &name, float &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, double &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(std::string &name, double &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, bool &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(std::string &name, bool &val);
};

#endif
