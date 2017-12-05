#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: FileSystem.h

Class: FileSystem

Description: Manages the input and output of files used by the game
*/


namespace tinyxml2 {
    class XMLDocument;
    class XMLElement;
}


class FileSystem {

public:

    class Iterator {


    };

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

        // Class Functions

    inline static FileSystem &Instance() {

        static FileSystem instance;

        return instance;
    }

    // Initialize the file system to a usable state
    bool initialize(const char *settingsLoc);

    // Initialize the file system to a usable state
    void initialize(const std::string &settingsLoc);

    // Set the file to be used for loading
    bool useFile(const char *fileRef);

    // Set the file to be used for loading
    bool useFile(const std::string &fileRef);


        // Loading Functions

    // Changes from current node to a contained element
    bool traverseToElement(const char *elem);

    // Changes from current node to a contained element
    bool traverseToElement(const std::string &elem);

    // Chamges from current node to the first child
    bool traverseToChildElement();

    // Changes from current element to the next element of same parent
    bool traverseToSyblingElement();

    // Changes from current element to the next element of same parent by name
    bool traverseToSyblingElement(const char *syb);

    // Changes from current element to the next element of same parent by name
    bool traverseToSyblingElement(const std::string &syb);

    // Return from current tag to parent tag
    bool traverseToParentElement();

    // Get the text contained in the tags of the current element
    bool getElementText(std::string &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, std::string &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const std::string &name, std::string &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, int &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const std::string &name, int &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, float &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const std::string &name, float &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, double &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const std::string &name, double &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const char *name, bool &val);

    // Get an attribute from the current element, if exists
    bool getAttribute(const std::string &name, bool &val);


        // Saving Functions

    // Save the given file to the location/filename
    bool saveFile(const char *refName, const char *fileName);

    // Save the given file to the location/filename
    bool saveFile(const std::string &refName, const std::string &fileName);

    // Create a new asset file. Is not automatically saved
    bool createTempFile(const char *refName);

    // Create a new asset file. Is not automatically saved
    bool createTempFile(const std::string &refName);

    // Load an existing file from location, returns false if doesn't exist
    bool loadFile(const char *refName, const char *fileLoc);

    // Load an existing file from location, returns false if doesn't exist
    bool loadFile(const std::string &refName, const std::string &fileLoc);

    // Create a new element as a child of the current element
    bool newElement(const char *name);
    
    // Create a new element as a child of the current element
    bool newElement(const std::string &name);

    // Add text to the current element
    bool setElementText(const char *text);

    // Add text to the current element
    bool setElementText(const std::string &text);

    // Add an attribute to the current element
    template <typename T>
    bool setElementAttribute(const char *attribute, const T val) {

        if (activeElem != NULL) {

            activeElem->SetAttribute(attribute, val);

            return true;
        }

        return false;
    }

    // Add an attribute to the current element
    template <typename T>
    bool setElementAttribute(const std::string &attribute, const T val) {

        return this->setElementAttribute(attribute.c_str(), val);
    }

    
        // Extra xml handling

    bool destroyCurrentElement();
};

#endif
