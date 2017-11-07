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

#include "tinyxml2.h"


class FileSystem {

private:

    /***** Variables *****/
 
    tinyxml2::XMLDocument assetsFile; // Note: Could not forward declare. Unsure why.
    tinyxml2::XMLDocument mapFile;

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
    bool initialize(const char *assets, const char *map);

    // Initialize the file system to a usable state
    void initialize(std::string &assets, std::string &map);

    // Load a zone from the map file
    void loadZone(const char *zone);
};

#endif
