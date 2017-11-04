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


class FileSystem {

private:

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
    void initialize(std::string &settingsFile);

    // Cycle update for file system
    void update();

    // Display relavent information from the file system to the screen
    void display();
};

#endif
